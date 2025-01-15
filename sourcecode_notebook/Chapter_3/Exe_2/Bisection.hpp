/*
 * Bisection.hpp
 *
 *  Created on: Oct 15, 2016
 *      Author: user
 */

#ifndef BISECTION_H_
#define BISECTION_H_

#include "rootfinding.hpp"
#include "Function.hpp"
#include "RootFinder.hpp"

class Bisection: public RootFinder{
  protected:
    real inf_limit;
    real sup_limit;

  public:
    Bisection(const Function & f, real inf_l, real sup_l, real tol, 
                const checkT& term_c, int max_i):
      RootFinder (f,tol,term_c,max_i), inf_limit(inf_l), sup_limit(sup_l){}
      
    real find_root(int & nit) const override;
};

#endif /* BISECTION_H_ */
