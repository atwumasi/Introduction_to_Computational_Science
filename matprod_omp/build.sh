gcc -o run_test prod_omp.c prod_opt_omp.c -std=c99 -lm -fopenmp
for NPROC in 1 2 4 #8 12 16 
do
  export OMP_NUM_THREADS=${NPROC}; 
  echo "Running with ${NPROC} processors:"
  ./run_test
done
