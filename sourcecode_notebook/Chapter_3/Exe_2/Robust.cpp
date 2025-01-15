/*
 * Robust.cpp
 *
 *  Created on: Oct 15, 2016
 *      Author: user
 */

#include "Robust.hpp"

real Robust::find_root(int & nit_bis, int & nit_newt) const
{
	Bisection bs(func,inf_limit,sup_limit,cratio * tolerance, termination_criteria,max_iteration);

	  // Call bisection method (with a greater desired tolerance)
	 real x_bis = bs.find_root(nit_bis);

	 /*
	    Call a Newton algorithm which uses as an initial value
	    the solution given by bisection method
	 */

	 Newton nw(func, x_bis, tolerance, termination_criteria, max_iteration);
	 return nw.find_root(nit_newt);
}

real Robust::find_root(int & nit) const
{
	int nit_bis,nit_newt;
	const real ret_value = find_root(nit_bis, nit_newt);
	nit= nit_bis + nit_newt;
	return ret_value;
}
