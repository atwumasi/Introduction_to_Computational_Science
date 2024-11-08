#include <stdio.h>

int main( int argc, char** argv ) {
  double a = 1.0;
  double b = 2.0;
  int    c1 = a/b;
  int    c2 = 1/2;
  double c3 = a/b;
  double c4 = 1/2;
  double c5 = 1/b;
  double c6 = a/2;
  double c9 = (double)1/2;

  int    c7 = 3.5;
  int    c8 = -3.5;

  printf("%d\n",c1);
  printf("%d\n",c2);
  printf("%lf\n",c3);
  printf("%lf\n",c4);
  printf("%lf\n",c5);
  printf("%lf\n",c6);
  printf("%d\n",c7);
  printf("%d\n",c8);
  printf("%lf\n",c9);

  return 0;
}
