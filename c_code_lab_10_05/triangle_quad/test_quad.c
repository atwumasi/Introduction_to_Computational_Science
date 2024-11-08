#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "quad.h"

double algebraic(double,double);

int main( int argc, char** argv ) {
  int    N      = atoi(argv[1]);
  double X[3], Y[3];
  // Read the six coordinates of the triangle
  for ( int i = 0; i < 3; i++ ) {
    X[i] = atof(argv[2+2*i]);
    Y[i] = atof(argv[3+2*i]);
  }

  real2DFun f = &algebraic;

  double val = 0.0, dX[2] = {(X[1]-X[0])/N,(X[2]-X[0])/N},
         dY[2] = {(Y[1]-Y[0])/N,(Y[2]-Y[0])/N};
  for ( int i = 0; i < N; i++ ) {
    for ( int j = 0; j < N-i; j++ ) {
      double loc_x = X[0] + i*dX[0] + j*dX[1];
      double loc_y = Y[0] + i*dY[0] + j*dY[1];
      double x[3] = {loc_x, loc_x+dX[0], loc_x+dX[1]};
      double y[3] = {loc_y, loc_y+dY[0], loc_y+dY[1]};
      val += QuadTria(x,y,f);
    }
  }
  for ( int i = 1; i <= N-1; i++ ) {
    for ( int j = 1; j <= N-i; j++ ) {
      double loc_x = X[0] + i*dX[0] + j*dX[1];
      double loc_y = Y[0] + i*dY[0] + j*dY[1];
      double x[3] = {loc_x, loc_x-dX[0], loc_x-dX[1]};
      double y[3] = {loc_y, loc_y-dY[0], loc_y-dY[1]};
      val += QuadTria(x,y,f);
    }
  }

  printf("The integral is: %f.\n", val);

  return 0;
}

double algebraic(double x, double y) {
  //return 2.0;
  return sqrt(cos(x)*cos(y)+2.0*sin(x)*sin(y));
}
