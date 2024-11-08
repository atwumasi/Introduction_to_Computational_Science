import numpy as np

def evol_fe( cfl, A ) :
  Adim = np.shape( A )
  I = np.eye( Adim[0] )
  return I - cfl * A

def evol_rk2( cfl, A ) :
  Adim = np.shape( A )
  I = np.eye( Adim[0] )
  A = np.matrix(A)
  return I - cfl * A + 0.5 * cfl * cfl * A * A
