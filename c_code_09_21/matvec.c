#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Compute a = Ab
double b[PROBSIZE];
double a[PROBSIZE];
double A[PROBSIZE][PROBSIZE];

int main( int argc, char** argv ) {

  for ( int i = 0; i < PROBSIZE; i++ )
    b[i] = ((double)rand()/(double)RAND_MAX);

  for ( int i = 0; i < PROBSIZE; i++ )
    for ( int j = 0; j < PROBSIZE; j++ )
      A[i][j] = ((double)rand()/(double)RAND_MAX);

  memset( a, 0, sizeof( a ) );

  clock_t start = clock(), diff;

  //for ( int i = 0; i < PROBSIZE; i++ )
  //  for ( int j = 0; j < PROBSIZE; j++ )
  //    a[i] += A[i][j] * b[j];

  for ( int j = 0; j < PROBSIZE; j++ )
    for ( int i = 0; i < PROBSIZE; i++ )
      a[i] += A[i][j] * b[j];

  diff = clock() - start;
  int msec = diff * 1000 / CLOCKS_PER_SEC;
  printf("Time taken %d seconds %d milliseconds\n", msec/1000, msec%1000);

  FILE* fp = fopen("matvec_result.txt", "w");
  for ( int i = 0; i < PROBSIZE; i++ )
    fprintf( fp, "%lf\n", a[i] );
  fclose( fp );

  return 0;
}
