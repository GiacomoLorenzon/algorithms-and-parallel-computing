/*!
  \file rootfinding.hpp
  \brief A collection of typedefs for rootfinding
*/

#ifndef ROOTFINDING_H
#define ROOTFINDING_H

#include <iostream>
#include <cmath>
#include <limits>

//! Type for real numbers
typedef double real;

//! Type for convergence check
enum checkT {
  INCREMENT, //! Check the difference between subsequent iterates
  RESIDUAL,  //! Check the residual
  BOTH       //! Check both conditions
};

#endif
