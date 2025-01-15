/*
 * Function.h
 *
 *  Created on: Oct 15, 2016
 *      Author: user
 */

#ifndef FUNCTION_H_
#define FUNCTION_H_

#include <vector>
#include "rootfinding.h"

class Function {
private:
  std::vector<real> coefficients;

public:
  Function (const std::vector<real> &coeff): coefficients(coeff){};
  real eval (real x) const;
  Function derivative (void) const;
  void print (void) const;
};

#endif /* FUNCTION_H_ */
