/*
 * RootFinder.hpp
 *
 *  Created on: Oct 15, 2016
 *      Author: user
 */

#ifndef ROOTFINDER_H_
#define ROOTFINDER_H_

#include "rootfinding.hpp"
#include "Function.hpp"

class   RootFinder {
protected:
  Function func;
  real tolerance;
  checkT termination_criteria;
  int max_iteration;

  bool converged (real increment, real residual,
          real tol, const checkT& check ) const;
public:
  RootFinder(const Function & f, real tol, const checkT& term_c, int max_i):
    func(f), tolerance(tol), termination_criteria(term_c), max_iteration(max_i){}
    
  virtual real find_root(int & nit) const = 0;
};

#endif /* ROOTFINDER_H_ */
