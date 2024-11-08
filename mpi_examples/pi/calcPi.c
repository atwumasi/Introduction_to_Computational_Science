#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include "mpi.h"

int main(int argc, char** argv) {
  int     n, my_pe_num, numprocs, index;
  double  mypi, pi, h, x;

  MPI_Init( &argc, &argv );
  MPI_Comm_size( MPI_COMM_WORLD, &numprocs );
  MPI_Comm_rank( MPI_COMM_WORLD, &my_pe_num );

  if ( my_pe_num == 0 ) {
    printf("How many intervals? \n" );
    scanf("%d", &n);
  }

  MPI_Bcast( &n, 1, MPI_INT, 0, MPI_COMM_WORLD );

  mypi = 0;
  h = (double) 2/n;

  // Version 1
  if ( false )
  {
    double start = (my_pe_num*2/numprocs)-1;
    double end = ((my_pe_num+1)*2/numprocs)-1;

    for ( x = start; x < end; x = x+h )
      mypi += h * 2 * sqrt(1-x*x);
  }
  
  // Version 2
  if ( true )
  {
    int start = my_pe_num*n/numprocs;
    int end   = (my_pe_num+1)*n/numprocs;
    for ( int i = start; i < end; i++ ) {
      x = h * i - 1.0;
      mypi += h * 2 * sqrt(1-x*x);
    }
  }

  MPI_Reduce( &mypi, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD );

  if ( my_pe_num == 0 ) {
    printf( "Pi is approximately %f\n", pi );
    printf( "Error is %f\n", pi-3.14159265358979323846 );
  }
  
  MPI_Finalize();
}
