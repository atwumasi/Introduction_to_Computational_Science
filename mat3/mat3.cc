#include <cstdio>
#include <cstdlib>
#include "mat3.h"

MAT3::MAT3(void) {
  MAT3(0.0);
}

MAT3::MAT3(const double val) {
  for ( int i = 0; i < 3; i++ )
    data[i] = 0.0;
  for ( int i = 0; i < 3; i++ )
    data[i][i] = val;
}

MAT3::MAT3(const VEC3& vec) {
  for ( int i = 0; i < 3; i++ )
    data[i] = 0.0;
  for ( int i = 0; i < 3; i++ )
    data[i][i] = vec[i];
}

MAT3::MAT3(const MAT3& mat) {
  for ( int i = 0; i < 3; i++ )
    data[i] = mat[i];
}

void MAT3::rand(void) {
  for ( int i = 0; i < 3; i++ )
    data[i].rand();
  return;
}

VEC3& MAT3::operator[] (int i) {
  return data[i];
}

const VEC3& MAT3::operator[] (int i) const {
  return data[i];
}

void MAT3::operator= (const MAT3& mat) {
  for ( int i = 0; i < 3; i++ )
    data[i] = mat[i];
  return;
}

void MAT3::operator+= (const MAT3& mat) {
  // Put your work here
  return;
}

void MAT3::operator-= (const MAT3& mat) {
  for ( int i = 0; i < 3; i++ )
    data[i] -= mat[i];
  return;
}

void MAT3::operator*= (const double val) {
  for ( int i = 0; i < 3; i++ )
    data[i] *= val;
  return;
}

void MAT3::operator*= (const MAT3& mat) {
  // Put your work here
  return;
}



//MAT3 mat1(1.0);
//MAT3 mat2(0.0);
//mat2 *= mat1; //mat2.operator=(mat1)
//mat2 = mat2 * mat1

void MAT3::operator/= (const double val) {
  for ( int i = 0; i < 3; i++ )
    data[i] /= val;
  return;
}

MAT3 operator+ (const MAT3& input_1, const MAT3& input_2) {
  // Put your work here

}

MAT3 operator+ (const MAT3& input_1) {
  MAT3 mat;
  for ( int i = 0; i < 3; i++ )
    mat[i] = input_1[i];
  return mat;
}

MAT3 operator- (const MAT3& input_1, const MAT3& input_2) {
  MAT3 mat;
  for ( int i = 0; i < 3; i++ )
    mat[i] = input_1[i] - input_2[i];
  return mat;
}

MAT3 operator- (const MAT3& input_1) {
  MAT3 mat;
  for ( int i = 0; i < 3; i++ )
    mat[i] = -input_1[i];
  return mat;
}

MAT3 operator* (const double& input_s, const MAT3& input_m) {
  // Put your work here
}

MAT3 operator* (const MAT3& input_m, const double& input_s) {
  MAT3 mat(input_m);
  for ( int i = 0; i < 3; i++ )
    mat[i] *= input_s;
  return mat;
}

MAT3 operator* (const MAT3& input_1, const MAT3& input_2) {
  MAT3 mat(0.0);
  for ( int i = 0; i < 3; i++ )
    for ( int j = 0; j < 3; j++ )
      for ( int k = 0; k < 3; k++ )
        mat[i][j] += input_1[i][k] * input_2[k][j];
  return mat;
}

MAT3 operator/ (const MAT3& input_m, const double& input_s) {
  MAT3 mat(input_m);
  for ( int i = 0; i < 3; i++ )
    mat[i] /= input_s;
  return mat;
}

VEC3 operator* (const MAT3& input_m, const VEC3& input_v) {
  // Put your work here
}

MAT3 operator^ (const VEC3& input_1, const VEC3& input_2) {
  MAT3 mat;
  for ( int i = 0; i < 3; i++ )
    for ( int j = 0; j < 3; j++ )
      mat[i][j] = input_1[i] * input_2[j];
  return mat;
}

std::ostream& operator<< (std::ostream& os, const MAT3& mat) {
  os << std::endl;
  for ( int i = 0; i < 3; i++ )
  {
    for ( int j = 0; j < 3; j++ )
      os << mat.data[i][j] << '\t';
    os << std::endl;
  }
  return os;
}

