gcc -c quad.c -std=c99 #-lm
gcc -c test_quad.c -std=c99 #-lm
gcc -o test_quad quad.o test_quad.o -std=c99 -lm
