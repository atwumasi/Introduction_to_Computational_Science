#include <iostream>
#include "vec.h"
using namespace std;

int main( int argc, char** argv ) {
  VEC<DIM> vec_1;
  vec_1.rand();
  cout << "Vector 1: " << vec_1;

  VEC<DIM> vec_2(vec_1);
  cout << "Vector 2: " << vec_2;

  VEC<DIM> vec_3(2.0);
  cout << "Vector 3: " << vec_3;

  cout << "Vector 1 + Vector 2: " << vec_1 + vec_2;
  cout << "Vector 1 + 1.0: " << vec_1 + 1.0;
  cout << "Vector 1 + Vector 2 / 2 - Vector 3: " << vec_1 + vec_2/2 - vec_3;
  cout << "-Vector 3: " << - vec_3;

#if DIM==3
  cout << "Vector 1 X Vector 3: " << ( vec_1 | vec_3 );
#endif

  return 0;
}
