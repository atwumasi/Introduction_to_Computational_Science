export OMP_NUM_THREADS=$1
gcc -fopenmp -o run_example omp_mat.c -std=c99
./run_example
