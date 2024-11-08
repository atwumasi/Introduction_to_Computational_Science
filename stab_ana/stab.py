import mypde.adveq.disc
import mypde.diffeq.disc
import mypde.time.exp
import mypde.time.imp
import numpy as np
import matplotlib.pyplot as plt

def plot_stab( cfl, n, prob, smeth, tmeth ) :
  if prob is "adv" :
    print "Advection: cfl = c dt / dx"
    if smeth is "upw" :
      A = mypde.adveq.disc.mat_upw( n )
    if smeth is "ord2" :
      A = mypde.adveq.disc.mat_ord2( n )
  if prob is "diff" :
    print "Diffusion: cfl = nu dt / dx / dx"
    if smeth is "cent2" :
      A = mypde.diffeq.disc.mat_cent2( n )
    if smeth is "cent4" :
      A = mypde.diffeq.disc.mat_cent4( n )

  if tmeth is "fe" :
    M = mypde.time.exp.evol_fe( cfl, A )
  if tmeth is "rk2" :
    M = mypde.time.exp.evol_rk2( cfl, A )
  if tmeth is "be" :
    M = mypde.time.imp.evol_be( cfl, A )
  if tmeth is "bdf2" : 
    M = mypde.time.imp.evol_bdf2( cfl, A )

  E = np.linalg.eigvals( M )
  theta = np.linspace( 0.0, 2.0*np.pi, 1001 )
  plt.plot( np.cos(theta), np.sin(theta), 'k-', np.real(E), np.imag(E), 'r*' )
  plt.show()
  return
