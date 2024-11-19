import numpy as np
from numpy import cos, sin
import matplotlib.pyplot as plt
from pyPLUTO import pload as pp
import pyPLUTO as pypl
import astropy.units as u
import astropy.constants as c
from scipy.interpolate import interp1d

UNIT_LENGTH = u.pc.to('cm')

# 'GA10' in atomdb. XYZ reference to Asplund et al. ARA&A. 2009
X = 0.7381
Y = 0.2485
Z = 0.0134

mu = 1/(2*X+3/4*Y+1/2*Z)
mu_e = 2/(1+X)
mu_H = 1/X
mu_i = 4/(3*X+1)

emissvity_file = "emissivity_0_8_atomdb_CIE.txt"
temp, emissivty = np.loadtxt(emissvity_file).T
lambda_interp = interp1d(np.log10(temp), np.log10(emissivty), kind='linear', bounds_error=False, fill_value=(np.log10(emissivty[0]), np.log10(emissivty[-1])))

D = pp.pload(1, datatype='dbl')
Tgrid = 1.203e8*(D.prs/D.rho*mu)
# dL = n_e*n_H*lambda(T)*dV
EmissivityGrid = (D.dx1*2*np.pi*D.x1**2)[:, np.newaxis]*(D.dx2*sin(D.x2))*UNIT_LENGTH**3*D.rho**2/mu_e/mu_H*10**lambda_interp(np.log10(Tgrid))
