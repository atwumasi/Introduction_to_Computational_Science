#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <float.h>
#include <math.h>
#include <omp.h>
#include "prod_opt_omp.h"

void gen_rand_mat(double A[][NUM]) {
  for ( int i = 0; i < NUM; i++ )
    for ( int j = 0; j < NUM; j++ )
      A[i][j] = (double)rand()/RAND_MAX;
  return;
}

double eval_time_prod_omp(double A[][NUM], double B[][NUM])
{
  double tot_time, loc_sum;
  double *row_a, *row_c;
  double begin, end;
  int i, j, k;
  double C[NUM][NUM];
  for ( i = 0; i < NUM; i++ )
    for ( j = 0; j < NUM; j++ )
      C[i][j] = 0.0;
  clear_cache();
  begin = omp_get_wtime();
  for ( i = 0; i < NUM; i++ ) {
    row_c = &C[i][0];
    row_a = &A[i][0];
    for ( j = 0; j < NUM; j++ ) {
      loc_sum = 0.0;
      for ( k = 0; k < NUM; k++ )
        loc_sum += *(row_a+k) * B[k][j];
      *(row_c+j) += loc_sum;
    }
  }
  end = omp_get_wtime();
  tot_time = end-begin;
  return tot_time;
}

void clear_cache(void) {
  const int size = 1024*1024;
  char *c = (char *)malloc(size);
  for (int i = 0; i < 100; i++)
    for (int j = 0; j < size; j++)
      c[j] = i*j;
  free(c);
  return;
}

