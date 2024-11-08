#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include "mpi.h"

#define DIM 1200

/* This program computes C = A B
 * where A, B, and C are DIM * DIM matrices,
 * and all storages are separeted row-wise
 * on multiple processors
 *
 * To fix the idea, let A_ij = cos(i+j)
 * and B_ij = sin(i-j)
 */

int main(int argc, char** argv) {
  int nproc, myrank;
  MPI_Init( &argc, &argv );
  MPI_Comm_size( MPI_COMM_WORLD, &nproc );
  MPI_Comm_rank( MPI_COMM_WORLD, &myrank );

  // Compute the number of rows on each processor
  int i_start, i_end;
  i_start = myrank * DIM / nproc;
  i_end = (myrank+1) * DIM / nproc;
  int nrow = i_end - i_start;
  int nrow_max = 0;

#ifdef DEBUG
  printf("This is processor with rank %d (out of %d), who's handling rows from %d to %d.\n", myrank, nproc, i_start, i_end);
#endif

  MPI_Allreduce( &nrow, &nrow_max, 1, MPI_INT, MPI_MAX, MPI_COMM_WORLD );

#ifdef DEBUG
  if ( myrank == 0 )
    printf("The maximum number of rows handled by a single processor is %d.\n", nrow_max);
#endif

  // Get the range for every processor
  int* i_range = malloc(2*nproc*sizeof(int));
  int i_range_loc[2] = {i_start, i_end};
  MPI_Gather( &(i_range_loc[0]), 2, MPI_INT, &(i_range[0]), 2, MPI_INT, 0, MPI_COMM_WORLD );
  MPI_Bcast( &(i_range[0]), 2*nproc, MPI_INT, 0, MPI_COMM_WORLD );

#ifdef DEBUG
  for ( int r = 0; r < nproc; r++ ) 
    printf("The range for rank %d on processor %d is: %d and %d.\n", r, myrank, i_range[2*r], i_range[2*r+1]);
#endif

  // Allocate the space
  double* A = (double*) malloc(nrow*DIM*sizeof(double));
  double* B = (double*) malloc(nrow*DIM*sizeof(double));
  double* C = (double*) calloc(nrow*DIM,sizeof(double)); // C is initialized to zero

  int i, j, k;

  // Initialize A and B
  for ( i = i_start; i < i_end; i++ )
    for ( j = 0; j < DIM; j++ )
      A[(i-i_start)*DIM+j] = cos(i+j);
  for ( i = i_start; i < i_end; i++ )
    for ( j = 0; j < DIM; j++ )
      B[(i-i_start)*DIM+j] = sin(i-j);

  // Computing C = C + A * B
  double wtime_loc;
  wtime_loc = MPI_Wtime();
  double* buff = (double*) malloc(nrow_max*DIM*sizeof(double));

  // First, adding own component
  for ( i = i_start; i < i_end; i++ )
    for ( j = 0; j < DIM; j++ )
      for ( k = i_start; k < i_end; k++ )
        C[(i-i_start)*DIM+j] += A[(i-i_start)*DIM+k] * B[(k-i_start)*DIM+j];
  
  // Next, loop over offset = 1, 2, ..., nproc-1, 
  // and processor r will send its B block to processor
  // r+offset while it also receives data from r-offset
  int offset, rank_to_send, rank_to_recv;
  MPI_Status st;
  int i_start_else, i_end_else, nrow_else;
  for ( offset = 1; offset < nproc; offset++ ) {
    rank_to_send = (myrank+offset<nproc) ? myrank+offset : myrank+offset-nproc;
    rank_to_recv = (myrank-offset>=0) ? myrank-offset : myrank-offset+nproc;
    i_start_else = i_range[2*rank_to_recv];
    i_end_else   = i_range[2*rank_to_recv+1];
    nrow_else    = i_end_else - i_start_else;

#ifdef DEBUG
    printf("Number of rows to send by proc %d to proc %d is: %d.\n", myrank, rank_to_send, nrow);
    printf("Number of rows to receive by proc %d from proc %d is: %d.\n", myrank, rank_to_recv, nrow_else);
#endif

    if (false) { // Version 1: deadlock for all nproc!
      MPI_Send( &(B[0]), nrow*DIM, MPI_DOUBLE, rank_to_send, 0, MPI_COMM_WORLD );
      MPI_Recv( &(buff[0]), nrow_else*DIM, MPI_DOUBLE, rank_to_recv, 0, MPI_COMM_WORLD, &st );
    }

    if (false) { // Version 2: deadlock for all nproc that's not a prime number!
      if ( myrank == 0 ) {
        MPI_Send( &(B[0]), nrow*DIM, MPI_DOUBLE, rank_to_send, 0, MPI_COMM_WORLD );
        MPI_Recv( &(buff[0]), nrow_else*DIM, MPI_DOUBLE, rank_to_recv, 0, MPI_COMM_WORLD, &st );
      }
      else {
        MPI_Recv( &(buff[0]), nrow_else*DIM, MPI_DOUBLE, rank_to_recv, 0, MPI_COMM_WORLD, &st );
        MPI_Send( &(B[0]), nrow*DIM, MPI_DOUBLE, rank_to_send, 0, MPI_COMM_WORLD );
      }
    }

    if (true) { // Version 3: no deadlock for all nproc
      MPI_Request request;
      MPI_Isend( &(B[0]), nrow*DIM, MPI_DOUBLE, rank_to_send, 0, MPI_COMM_WORLD, &request );
      MPI_Recv( &(buff[0]), nrow_else*DIM, MPI_DOUBLE, rank_to_recv, 0, MPI_COMM_WORLD, &st );
      MPI_Wait( &request, MPI_STATUS_IGNORE );
    }

    for ( i = i_start; i < i_end; i++ )
      for ( j = 0; j < DIM; j++ )
        for ( k = i_start_else; k < i_end_else; k++ )
          C[(i-i_start)*DIM+j] += A[(i-i_start)*DIM+k] * buff[(k-i_start_else)*DIM+j];

  }

  wtime_loc = MPI_Wtime() - wtime_loc;

  printf("The wall clock time on processor %d is %f.\n", myrank, wtime_loc);

  // Finally, compute the Frobenious norm of C, 
  // as a brief check on the correctness of C
  double C_norm_loc = 0.0, C_norm;
  
  for ( i = i_start; i < i_end; i++ )
    for ( j = 0; j < DIM; j++ )
      C_norm_loc += C[(i-i_start)*DIM+j] * C[(i-i_start)*DIM+j];

  MPI_Reduce( &C_norm_loc, &C_norm, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD );
  
  if ( myrank == 0 ) 
    printf("The Frobenious norm of the product matrix C is: %f.\n", sqrt(C_norm));

  free( A );
  free( B );
  free( C );
  free( buff );
  free( i_range );

  MPI_Finalize();

  return 0;
}
