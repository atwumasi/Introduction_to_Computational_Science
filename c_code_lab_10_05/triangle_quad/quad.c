#include "quad.h"
#include <math.h>
#include <stdio.h>

double QuadTria(double* x, double* y, real2DFun f) {
  double area = 0.5*fabs((x[1]*y[2]-x[2]*y[1])-(x[0]*y[2]-x[2]*y[0])+(x[0]*y[1]-x[1]*y[0]));
  return (1.0/3.0) * area * ( (*f)(x[0],y[0]) + (*f)(x[1],y[1]) + (*f)(x[2],y[2]) );
}

