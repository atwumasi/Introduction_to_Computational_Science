#include <stdio.h>
#include <stdlib.h>

#ifndef BLKSIZE
#define BLKSIZE 120
#endif
#define MAX     18000
#define NUM_BLK (MAX/BLKSIZE)

int main( int argc, char** argv ) {

  double* A = (double*)malloc(MAX*MAX*sizeof(double));
  double* B = (double*)malloc(MAX*MAX*sizeof(double));
  //double* loc_A;

  for ( int i = 0; i < MAX; i+=BLKSIZE )
    for ( int j = 0; j < MAX; j+=BLKSIZE ) {
      //loc_A = A+i*MAX;
      for ( int ii = i; ii < i + BLKSIZE; ii++ ) {
        for ( int jj = j; jj < j + BLKSIZE; jj++ )
          A[ii*MAX+jj] = A[ii*MAX+jj] + B[jj*MAX+ii];
          //loc_A[jj] = loc_A[jj] + B[jj*MAX+ii];
        //loc_A += MAX;
      }
    }

  free( A );
  free( B );

  return 0;
}

