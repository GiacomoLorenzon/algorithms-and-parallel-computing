/*
 * Bisection.h
 *
 *  Created on: Oct 15, 2016
 *      Author: user
 */

#ifndef BISECTION_H_
#define BISECTION_H_

#include "rootfinding.h"
#include "Function.h"

class Bisection{
	private:
		Function func;
		real inf_limit;
		real sup_limit;
		real tolerance;
		checkT termination_criteria;
		int max_iteration;

		bool converged (real increment, real residual,
		        real tol, const checkT& check ) const;
	public:
		Bisection (const Function  &f, real inf_l, real sup_l, real tol, 
			const checkT& term_c, int max_i):
			func(f), inf_limit(inf_l), sup_limit(sup_l), tolerance(tol),
			termination_criteria(term_c), max_iteration(max_i){}
		real find_root(int & nit) const;
};

#endif /* BISECTION_H_ */
