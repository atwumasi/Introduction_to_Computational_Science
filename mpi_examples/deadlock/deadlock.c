#include <stdio.h>
#include <assert.h>
#include <mpi.h> 

int main (int argc, char** argv) {
  int myrank, size;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &myrank); 
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Status status;
  MPI_Request request;
  double loc_val, other_val;

  assert( size >= 2 );

  if ( myrank == 0 ) {
    loc_val = 0.0;
    MPI_Recv(&other_val,1,MPI_DOUBLE,1,0,MPI_COMM_WORLD,&status);
    //MPI_Irecv(&other_val,1,MPI_DOUBLE,1,0,MPI_COMM_WORLD,&request);
    MPI_Send(&loc_val,1,MPI_DOUBLE,1,0,MPI_COMM_WORLD);
    MPI_Wait(&request,&status);
    printf( "Value pair on proc %d: (%lf,%lf).\n", myrank, loc_val, other_val );
  }

  if ( myrank == 1 ) {
    loc_val = 1.0;
    MPI_Recv(&other_val,1,MPI_DOUBLE,0,0,MPI_COMM_WORLD,&status);
    //MPI_Irecv(&other_val,1,MPI_DOUBLE,0,0,MPI_COMM_WORLD,&request);
    MPI_Send(&loc_val,1,MPI_DOUBLE,0,0,MPI_COMM_WORLD);
    MPI_Wait(&request,&status);
    printf( "Value pair on proc %d: (%lf,%lf).\n", myrank, loc_val, other_val );
  }

  MPI_Finalize();
  return 0;
}
