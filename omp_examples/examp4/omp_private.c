#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

int main( int argc, char** argv ) {
  int a[10];
  for ( int i = 0; i < 10; i++ ) a[i] = 0;
  int i, j = 10;

#pragma omp parallel for lastprivate(i,j) firstprivate(j)
  for ( i = 0; i < 10; i+=3 ) {
    j = j + i;
    printf( " Current j is %d in iteration %d.\n", j, i );
    a[i] = i*j;
  }

  printf( " Last index: %d; Value of j: %d.\n", i, j );
  for ( int i = 0; i < 10; i++ ) printf( " %2d ", a[i] );
  printf( "\n" );

  return 0;
}


