/* ///////////////////////////////////////////////////////////////////// */
/*!
  \file
  \brief Stellar wind test problem.

  Sets initial condition for a spherically symmetric radial wind blowing 
  from the origin of coordinates, see [Mig14].
  The initial condition consists of a constant-density ambient medium with 
  \f[
     \rho = \rho_a \,,\qquad  p = p_a\,,\qquad \vec{v} = v_{csm}\hvec{j} 
  \f]
  where \c v_csm is the velocity of the star with respect to the background.
  The wind is injeted using the \c INTERNAL_BOUNDARY where flow quantities are
  kept constant in time and equal to 
  \f[
     r^2v_r\rho = \rho_0 V_0^2r_0^2 \,,\qquad
     v_r = V_0\hvec{r} \,,\qquad
     p   = \frac{c_s^2}{\Gamma}\rho^\Gamma
  \f]
  These value are defined through the  UserDefBoundary() function when
  \c side is equal to 0. 

  Dimensions are chosen so that the spherical wind shell has radius 1,
  density 1 and velocity 1 (\f$ r_0 = V_0 = \rho_0 = 1\f$).
  
  The input parameters that control the problem dynamics are
  
  - <tt>g_inputParam[CS_WIND]</tt>: sets the sound speed in the wind region;
  - <tt>g_inputParam[RHO_AMB]</tt>: sets the ambient density
  - <tt>g_inputParam[CS_AMB]</tt>:  sets the ambient sound speed;
  - <tt>g_inputParam[V_CSM]</tt>:   sets the velocity of the star with 
                                    respect to the background;

  Configurations #01-05 and #07-08 work in 2D cylindrical axisymmetric
  coordinates while conf. #06 is 3D Cartesian.
  An AMR setup is available with configuration #04.

  \image html hd_stellar_wind.08.jpg "Density map at the end of computation for configuration #8"

  \author A. Mignone (mignone@to.infn.it)
  \date   July 12, 2019

  \b References
     - [Mig14]: "High-order conservative reconstruction schemes for finite
       volume methods in cylindrical and spherical coordinates",
       Mignone, JCP (2014) 270, 784 
*/
/* ///////////////////////////////////////////////////////////////////// */
#include "pluto.h"

/* ********************************************************************* */
void Init (double *us, double x1, double x2, double x3)
/*
 *
 *********************************************************************** */
{
  double rho, cs, R;

  us[RHO] = 1000*0.62;
  us[PRS] = us[RHO]*1.e4/(KELVIN*0.62);

  us[VX1] = 0.0;
  us[VX2] = 0.0;
  us[VX3] = 0.0;

  us[TRC] = 0.0;
}

/* ********************************************************************* */
void InitDomain (Data *d, Grid *grid)
/*! 
 * Assign initial condition by looping over the computational domain.
 * Called after the usual Init() function to assign initial conditions
 * on primitive variables.
 * Value assigned here will overwrite those prescribed during Init().
 *
 *
 *********************************************************************** */
{
}


/* **************************************************************** */
void Analysis (const Data *d, Grid *grid)
/*
 *
 ****************************************************************** */
{

}

/* ********************************************************************* */
void UserDefBoundary (const Data *d, RBox * box, int side, Grid *grid) 
/*
 * Sets inflow boundary condition at the top boundary (side == X2_END)
 * and the stellar wind region when side == 0.
 *
 *********************************************************************** */
{
  int   i, j, k, nv;
  double *x1, *x2, *x3;
  double  r, r0, cs;
  double  Vwind  = 1.0, rho, vr;

  x1 = grid->xgc[IDIR];
  x2 = grid->xgc[JDIR];
  x3 = grid->xgc[KDIR];

  if (side == 0){
    r0 = 1.0;
    cs = g_inputParam[CS_WIND];
    TOT_LOOP(k,j,i){ 
      #if GEOMETRY == CARTESIAN
      r  = sqrt(x1[i]*x1[i] + x2[j]*x2[j] + x3[k]*x3[k]);
      if (r <= r0){  
        vr    = tanh(r/r0/0.1)*Vwind;
        rho   = Vwind*r0*r0/(vr*r*r);
        d->Vc[RHO][k][j][i] = rho;
        d->Vc[VX1][k][j][i] = Vwind*x1[i]/r;
        d->Vc[VX2][k][j][i] = Vwind*x2[j]/r;
        d->Vc[VX3][k][j][i] = Vwind*x3[k]/r;
        d->Vc[PRS][k][j][i] = cs*cs/g_gamma*pow(rho,g_gamma);
        d->flag[k][j][i]   |= FLAG_INTERNAL_BOUNDARY;
      }    
      #elif GEOMETRY == CYLINDRICAL
      r  = sqrt(x1[i]*x1[i] + x2[j]*x2[j]);
      if (r <= r0){  
        vr    = tanh(r/r0/0.1)*Vwind;
        rho   = Vwind*r0*r0/(vr*r*r);
        d->Vc[RHO][k][j][i] = rho;
        d->Vc[VX1][k][j][i] = Vwind*x1[i]/r;
        d->Vc[VX2][k][j][i] = Vwind*x2[j]/r;
        d->Vc[VX3][k][j][i] = 0.0;
        d->Vc[PRS][k][j][i] = cs*cs/g_gamma*pow(rho,g_gamma);
        d->flag[k][j][i]   |= FLAG_INTERNAL_BOUNDARY;
      }    
      #elif GEOMETRY == POLAR
      r  = sqrt(x1[i]*x1[i] + x3[k]*x3[k]);
      if (r <= r0){  
        vr    = tanh(r/r0/0.1)*Vwind;
        rho   = Vwind*r0*r0/(vr*r*r);
        d->Vc[RHO][k][j][i] = rho;
        d->Vc[VX1][k][j][i] = Vwind*x1[i]/r;
        d->Vc[VX2][k][j][i] = 0.0;
        d->Vc[VX3][k][j][i] = Vwind*x3[k]/r;
        d->Vc[PRS][k][j][i] = cs*cs/g_gamma*pow(rho,g_gamma);
        d->flag[k][j][i]   |= FLAG_INTERNAL_BOUNDARY;
      }    
      #endif
    }
  }

  if (side == X1_BEG) {
    double r;
    X1_BEG_LOOP(k,j,i){
      r = x1[i];
      d->Vc[RHO][k][j][i] = 1.7e5*0.62/(r/0.01)/(r/0.01);
      d->Vc[PRS][k][j][i] = d->Vc[RHO][k][j][i]*34.7*pow(r/0.01, -1.28)*1.16e7/(KELVIN*0.62);

      d->Vc[VX1][k][j][i] = 3.0;
      d->Vc[VX2][k][j][i] = 0.0;
      d->Vc[VX3][k][j][i] = 0.0;

      d->Vc[TRC][k][j][i] = 1.0;
    }
  }
}
