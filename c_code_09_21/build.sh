#gcc -o intchar intchar.c -std=c99 -lm
#gcc -o real real.c -std=c99 -lm
#gcc -o matvec matvec.c -std=c99 -lm -DPROBSIZE=12000
gcc -o matmat matmat.c -std=c99 -lm -DPROBSIZE=1200
