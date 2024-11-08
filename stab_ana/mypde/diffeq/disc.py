import numpy as np

def mat_cent2( n ) :
  A = np.zeros( (n,n) )
  A[0,n-1] = -1
  A[n-1,0] = -1
  for i in range(0,n) :
    A[i,i] = 2
  for i in range(1,n) :
    A[i,i-1] = -1
    A[i-1,i] = -1
  return A

def mat_cent4( n ) :
  A = np.zeros( (n,n) )
  A[0,n-2] = 1.0/12.0
  A[0,n-1] = -16.0/12.0
  A[1,n-1] = 1.0/12.0
  A[n-2,0] = 1.0/12.0
  A[n-1,0] = -16.0/12.0
  A[n-1,1] = 1.0/12.0
  for i in range(0,n) :
    A[i,i] = 30.0/12.0
  for i in range(1,n) :
    A[i,i-1] = -16.0/12.0
    A[i-1,i] = -16.0/12.0
  for i in range(2,n) :
    A[i,i-2] = 1.0/12.0
    A[i-2,i] = 1.0/12.0
  return A

