#include <iostream>
#include <cstring>

template<class T> void sort_three(T& x, T& y, T& z) {
  T all_min;
  T all_max;

  if ( x < y )
    all_min = x;
  else
    all_min = y;
  if ( z < all_min )
    all_min = z;

  if ( x < y )
    all_max = y;
  else
    all_max = x;
  if ( all_max < z )
    all_max = z;
  
  y = x + y + z - all_min - all_max;
  x = all_min;
  z = all_max;
  return;
}

int main(int argc, char** argv) {
  int x = std::atoi(argv[1]);
  int y = std::atoi(argv[2]);
  int z = std::atoi(argv[3]);
  sort_three<int>(x,y,z);
  std::cout << "Sorted three integers are: " << x << ", " << y << ", " << z << "." << std::endl;
  return 0;
}
