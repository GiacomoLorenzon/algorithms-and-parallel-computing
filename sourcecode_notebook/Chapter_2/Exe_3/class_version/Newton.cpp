/*
 * Newton.cpp
 *
 *  Created on: Oct 15, 2016
 *      Author: user
 */

#include "Newton.h"

bool Newton::converged(real increment, real residual,
        real tol, const checkT& check) const {

  switch(check){
  case INCREMENT:
      return (increment < tol);
  case RESIDUAL:
      return (residual < tol);
  case BOTH:
      return ((increment < tol)&&(residual < tol));
  default:
      return false;
  }

}

real Newton::find_root(int & nit) const
{
  real xp = x_init;
  real v = func.eval(xp);
  real xnew = std::numeric_limits<double>::quiet_NaN();

  nit = 0;
  bool stop = false;
  for(int k = 1; k <= max_iteration && ! stop; ++k,++nit) {
      real derv = der.eval(xp);
      if(!derv) {
        std::cerr << "ERROR: Division by 0 occurred in Newton algorithm"
          << std::endl;
      }
      else
      {
        xnew = xp - v / derv;
        v = func.eval(xnew);
        stop = converged(fabs(xnew - xp), fabs(v),tolerance,termination_criteria);
        xp = xnew;
      }
  }
  return xnew;
}
