/*
 * Robust.hpp
 *
 *  Created on: Oct 15, 2016
 *      Author: user
 */

#ifndef ROBUST_H_
#define ROBUST_H_

#include "Newton.hpp"
#include "Bisection.hpp"

class Robust: public Bisection {

private:
  real cratio;

public:
  Robust(const Function & f, real inf_l, real sup_l, real tol, real cr, 
            const checkT& term_c, int max_i):
    Bisection (f,inf_l, sup_l, tol,term_c,max_i),cratio(cr){}
    
  real find_root(int & nit_bis, int & nit_newt) const;
  real find_root(int & nit) const override;
};

#endif /* ROBUST_H_ */
