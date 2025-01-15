/*
 * Function.h
 *
 *  Created on: Oct 15, 2016
 *      Author: user
 */

#ifndef FUNCTION_H_
#define FUNCTION_H_

#include <iostream>
#include <vector>

class Function
{
private:
  std::vector<double> coefficients;

public:
  Function (std::vector<double> coeff): coefficients (coeff) {};
  double eval (const double x) const;
  Function derivative() const;
  void print() const;
};

#endif /* FUNCTION_H_ */
