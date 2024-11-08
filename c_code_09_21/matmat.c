#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Compute A = BC
double A[PROBSIZE][PROBSIZE];
double B[PROBSIZE][PROBSIZE];
double C[PROBSIZE][PROBSIZE];

int main( int argc, char** argv ) {

  for ( int i = 0; i < PROBSIZE; i++ )
    for ( int j = 0; j < PROBSIZE; j++ )
    {
      B[i][j] = ((double)rand()/(double)RAND_MAX);
      C[i][j] = ((double)rand()/(double)RAND_MAX);
    }

  memset( A, 0, sizeof( A[0][0] ) * PROBSIZE * PROBSIZE );

  clock_t start = clock(), diff;

  for ( int i = 0; i < PROBSIZE; i++ )
    for ( int j = 0; j < PROBSIZE; j++ )
      for ( int k = 0; k < PROBSIZE; k++ )
        A[i][j] += B[i][k] * C[k][j];

  //for ( int k = 0; k < PROBSIZE; k++ )
  //  for ( int j = 0; j < PROBSIZE; j++ )
  //    for ( int i = 0; i < PROBSIZE; i++ )
  //      A[i][j] += B[i][k] * C[k][j];


  diff = clock() - start;
  int msec = diff * 1000 / CLOCKS_PER_SEC;
  printf("Time taken %d seconds %d milliseconds\n", msec/1000, msec%1000);

  FILE* fp = fopen("matmat_result.txt", "w");
  for ( int i = 0; i < PROBSIZE; i++ )
  {
    for ( int j = 0; j < PROBSIZE; j++ )
      fprintf( fp, "%lf\t", A[i][j] );
    fprintf( fp, "\n" );
  }
  fclose( fp );

  return 0;
}
