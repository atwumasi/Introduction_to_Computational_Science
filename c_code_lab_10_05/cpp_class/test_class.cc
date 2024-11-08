#include <iostream>
#include <cstdlib>

class array {
  public:
    array(int size) {
      // Complete this section so that size_ is assigned size
      // and array_ is allocated with size_ double variables
      // Include any library as you need.
      size_ = size;
      array_ = (double*)std::malloc(size_*sizeof(double));
    }
    ~array(void) {
      std::cout << "Removing " << size_ << " double variables" << std::endl;
      // Complete this section so that the array_ is 
      // freed.
      // Include any library as you need.
      std::free(array_);
    }

  private:
    int size_;
    double* array_;
};

int main(int argc, char** argv) {
  array myArray1(15);
  //array myArray2;
  array** myArrays = new array*[10];
  for ( int i = 1; i <= 10; i++ )
    myArrays[i-1] = new array(i);
  for ( int i = 1; i <= 10; i++ )
    delete myArrays[i-1];
  delete[] myArrays;
  return 0;
}
