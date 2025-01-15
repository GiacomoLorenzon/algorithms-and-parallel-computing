/*
 * Bisection.cpp
 *
 *  Created on: Oct 15, 2016
 *      Author: user
 */

#include "Bisection.h"

#include <cstdlib>

bool Bisection::converged(real increment, real residual,
        real tol, const checkT& check ) const {

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

real Bisection::find_root(int & nit) const
{
    real a=inf_limit;
    real b=sup_limit;
    real u = func.eval(a);  // Evaluate f on boundary a
    real l = b - a;         // Interval length
    real r;                 // Residual
    real c = a+l;           // Middle point

    nit = 0;
    r = func.eval(c);

    if (u*func.eval(b)>=0.0) {
    std::cout<<"Error Function has same sign at both endpoints"<<std::endl;
    return - std::numeric_limits<double>::infinity();
    }

    while ( !(converged(fabs(l), fabs(r), tolerance, termination_criteria))
            && (nit <= max_iteration) ) {

        (u*r < 0.) ? (b = c) : (a = c, u = r);
        l *= 0.5;
        c = a + l;
        r = func.eval(c);
        ++nit;
    }
    return c;
}
