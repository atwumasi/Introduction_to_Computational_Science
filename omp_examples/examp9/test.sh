for NPROC in 1 2 4 #3 4 #5 6 8 10 12 16 20
do
  export OMP_NUM_THREADS=${NPROC}
  echo $OMP_NUM_THREADS
  gcc -fopenmp -o run_example prod_omp.c -std=c99 -lm
  ./run_example
done
