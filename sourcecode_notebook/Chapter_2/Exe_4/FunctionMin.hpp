/*
 * FunctionMin.h
 *
 *  Created on: Oct 30, 2016
 *      Author: user
 */

#ifndef FUNCTIONMIN_H_
#define FUNCTIONMIN_H_

#include "Function.h"

class FunctionMin
{
  Function f;
  double inf_limit;
  double sup_limit;
  double tolerance;
  double step;
  unsigned int max_iterations;

  //gradient descent with x_init initial point
  double solve (double x_init) const;

public:
  FunctionMin (Function func, double a, double b, double tol,
               double s, unsigned int max_it)
    : f (func), inf_limit (a), sup_limit (b), tolerance (tol),
      step (s), max_iterations (max_it) {};

  // gradient descent
  double solve (void) const;
  // gradient descent with multi-start
  double solve_multistart (unsigned int n_trials) const;
  // gradient descent with multi-start and domain decomposition
  double solve_domain_decomposition (unsigned int n_intervals,
                                     unsigned int n_trials) const;
};

#endif /* FUNCTIONMIN_H_ */
