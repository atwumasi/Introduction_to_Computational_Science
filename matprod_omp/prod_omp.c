#include <stdlib.h>
#include <stdio.h>
#include "prod_opt_omp.h"

double A[NUM][NUM];
double B[NUM][NUM];

int main( int argc, char** argv ) {

  gen_rand_mat(A);
  gen_rand_mat(B);

  printf("Matrix-matrix multiplication uses %f secs.\n", eval_time_prod_omp(A,B));
  return 0;
}
