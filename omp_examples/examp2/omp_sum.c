#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

int main( int argc, char** argv ) {
  int a[12], b[12], c[12];

  for ( int i = 0; i < 12; i++ ) {a[i] = 11*i; b[i] = -i; }

  for ( int i = 0; i < 12; i++ ) printf( "%3d ", a[i] );
  printf( "\n" );

  for ( int i = 0; i < 12; i++ ) printf( "%3d ", b[i] );
  printf( "\n" );

//#pragma omp parallel for
//  {
//  }
//#pragma omp for
#pragma omp parallel
  {
#pragma omp for
    for ( int i = 0; i < 12; i++ ) {
      printf( "Thread %d, loop %d.\n", omp_get_thread_num(), i );
      c[i] = a[i] + b[i];
    }
  }

  for ( int i = 0; i < 12; i++ ) printf( "%3d ", c[i] );
  printf( "\n" );

  return 0;
}


