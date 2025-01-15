/*
 * Robust.h
 *
 *  Created on: Oct 15, 2016
 *      Author: user
 */

#ifndef ROBUST_H_
#define ROBUST_H_

#include "Bisection.h"
#include "Newton.h"

class Robust {
private:
	Function func;
	real inf_limit;
	real sup_limit;
	real tolerance;
	real cratio;
	checkT termination_criteria;
	int max_iteration;

public:
	Robust(const Function  &f, real inf_l, real sup_l, real tol, real cr, 
		const checkT& term_c, int max_i):
		func(f), inf_limit(inf_l), sup_limit(sup_l), tolerance(tol),
		cratio(cr), termination_criteria(term_c), max_iteration(max_i){}
	real find_root(int & nit_bis, int & nit_newt) const;
};

#endif /* ROBUST_H_ */
