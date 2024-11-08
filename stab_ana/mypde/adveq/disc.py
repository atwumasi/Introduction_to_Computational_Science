import numpy as np

def mat_upw( n ) :
  A = np.zeros( (n,n) )
  A[0,n-1] = -1
  for i in range(0,n) :
    A[i,i] = 1
  for i in range(1,n) :
    A[i,i-1] = -1
  return A

def mat_ord2( n ) :
  A = np.zeros( (n,n) )
  A[0,n-2] = 0.5
  A[0,n-1] = -2
  A[1,n-1] = 0.5
  for i in range(0,n) :
    A[i,i] = 1.5
  for i in range(1,n) :
    A[i,i-1] = -2
  for i in range(2,n) :
    A[i,i-2] = 0.5
  return A

