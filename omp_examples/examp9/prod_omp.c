#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <float.h>
#include <math.h>
#include <time.h>
#include <omp.h>
#define NUM     480

void gen_rand_mat(double A[][NUM]);
void eval_time_prod_omp(double A[][NUM], double B[][NUM], double* cpu_time, double* wall_time);

int main( int argc, char** argv ) {
  double A[NUM][NUM];
  double B[NUM][NUM];

  gen_rand_mat(A);
  gen_rand_mat(B);

  double cpu_time, wall_time;
  eval_time_prod_omp(A,B,&cpu_time,&wall_time);
  printf("Matrix-matrix multiplication: %f secs (CPU), %f secs (Wall).\n", cpu_time, wall_time);
  
  return 0;
}

void gen_rand_mat(double A[][NUM]) {
  for ( int i = 0; i < NUM; i++ )
    for ( int j = 0; j < NUM; j++ )
      A[i][j] = (double)rand()/RAND_MAX;
  return;
}

void eval_time_prod_omp(double A[][NUM], double B[][NUM], double* cpu_time, double* wall_time)
{
  double loc_sum;
  double *row_a, *row_c;
  double start_wall_time, end_wall_time;
  time_t start_cpu_time, end_cpu_time;
  int i, j, k;
  double C[NUM][NUM];
  for ( i = 0; i < NUM; i++ )
    for ( j = 0; j < NUM; j++ )
      C[i][j] = 0.0;
  start_cpu_time  = clock();
  start_wall_time = omp_get_wtime();
//#pragma omp parallel for private(row_c, row_a, loc_sum, j, k)
  for ( i = 0; i < NUM; i++ ) {
    row_c = &C[i][0];
    row_a = &A[i][0];
//#pragma omp parallel for private(loc_sum, k)
    for ( j = 0; j < NUM; j++ ) {
      loc_sum = 0.0;
#pragma omp parallel for reduction(+:loc_sum)
      for ( k = 0; k < NUM; k++ )
        loc_sum += *(row_a+k) * B[k][j];
      *(row_c+j) += loc_sum;
    }
  }
  end_wall_time = omp_get_wtime();
  end_cpu_time  = clock(); 
  *wall_time = end_wall_time - start_wall_time;
  *cpu_time  = (double)(end_cpu_time - start_cpu_time)/CLOCKS_PER_SEC;
  return;
}

