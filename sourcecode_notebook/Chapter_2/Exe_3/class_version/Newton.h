/*
 * Newton.h
 *
 *  Created on: Oct 15, 2016
 *      Author: user
 */

#ifndef NEWTON_H_
#define NEWTON_H_

#include <cstdlib>

#include "rootfinding.h"
#include "Function.h"

class Newton {
private:
		Function func;
		Function der;
		real x_init;
		real tolerance;
		checkT termination_criteria;
		int max_iteration;

		bool converged (real increment, real residual,
		        real tol, const checkT& check ) const;
	public:
		Newton(const Function  &f, real xp, real tol, const checkT& term_c, 
			int max_i):
			func(f), der(f.derivative()), x_init(xp), tolerance(tol),
			termination_criteria(term_c), max_iteration(max_i){
		}
		real find_root(int & nit) const;
};

#endif /* NEWTON_H_ */
