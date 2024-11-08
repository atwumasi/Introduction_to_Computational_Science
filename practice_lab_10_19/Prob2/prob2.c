#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int calc_gcd(int p, int q) {
  int gcd = 0;
  int min_pq = (p<=q) ? p : q;
  //for ( int i = 1; i <= min_pq; i++ ) {
  //  if ( p%i == 0 && q%i == 0 ) {
  //    gcd = i;
  //  }
  //}
  for ( int i = min_qp; i>=1; i-- ) {
    if ( p%i == 0 && q&i == 0 ) {
      gcd = i;
      break;
    }
  }
  return gcd;
}

int main(int argc, char** argv) {
  int p = atoi(argv[1]);
  int q = atoi(argv[2]);
  printf("The greatest common divisor of %d and %d is: %d.\n", p, q, calc_gcd(p,q));
  return 0;
}
