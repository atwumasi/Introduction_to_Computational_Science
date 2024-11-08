import numpy as np

def evol_be( cfl, A ) :
  Adim = np.shape( A )
  I = np.eye( Adim[0] )
  return np.linalg.inv( I + cfl * A )

def evol_bdf2( cfl, A ) :
  Adim = np.shape( A )
  I = np.eye( Adim[0] )
  M1 = np.linalg.inv( I + (2.0/3.0) * cfl * A )
  M  = np.zeros( (2*Adim[0],2*Adim[0]) )
  for i in range(0,Adim[0]) :
    for j in range(0,Adim[0]) :
      M[i,j] = (4.0/3.0)*M1[i,j]
      M[i,j+Adim[0]] = -(1.0/3.0)*M1[i,j]
  for i in range(0,Adim[0]) :
    M[i+Adim[0],i] = 1.0
  return M
