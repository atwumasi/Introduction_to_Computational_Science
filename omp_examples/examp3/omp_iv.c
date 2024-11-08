#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

int main( int argc, char** argv ) {
  double height[12], width[12], weight[12];
  double area = -1.0, density = 1.0;
  int i;

  for ( i = 0; i < 12; i++ ) height[i] = width[i] = 1.0*i;

#pragma omp parallel for private(area)
//#pragma omp parallel for
  for ( i = 0; i < 12; i++ ) {
    area = height[i] * width[i]; sleep( 0.2 );
    weight[i] = area * density; }

  printf( "The value of area in master thread is: %f.\n", area );
  for ( i = 0; i < 12; i++ ) printf( "%3.1lf ", weight[i] );
  printf( "\n" );

  return 0;
}


