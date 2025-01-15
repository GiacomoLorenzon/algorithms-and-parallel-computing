/*
 * RootFinder.cpp
 *
 *  Created on: Oct 15, 2016
 *      Author: user
 */

#include "RootFinder.hpp"

bool RootFinder::converged (real increment, real residual,
        real tol, const checkT& check ) const {
  /*
    Compares a parameter value against desired tolerance.
    The parameter is chosen upon the value of check.
  */
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
