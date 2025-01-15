/*
 * Newton.cpp
 *
 *  Created on: Oct 15, 2016
 *      Author: user
 */

#include "Newton.hpp"

real Newton::find_root(int & nit) const
{
	  real xp=x_init;
	  real v = func.eval(xp);
	  real xnew;
	  //Function der=func.derivative();
	  nit = 0;
	  bool conv=false;

	  for(int k = 1; k <= max_iteration && !conv; ++k,++nit) {
	    real derv = der.eval(xp);
	    if(!derv) {
	      std::cerr << "ERROR: Division by 0 occurred in Newton algorithm"
	        << std::endl;
	      exit(1);
	    }

	    xnew = xp - v / derv;
	    v = func.eval(xnew);
	    conv=converged(fabs(xnew - xp), fabs(v),tolerance,termination_criteria);
	    if(!conv)
	    	xp = xnew;
	  }
	  return xnew;
}
