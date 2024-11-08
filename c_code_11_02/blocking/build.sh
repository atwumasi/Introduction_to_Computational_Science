gcc -o run_reg mat_reg.c -std=c99 -DBLKSIZE=120
gcc -o run_blk mat_blocking.c -std=c99 -DBLKSIZE=120
