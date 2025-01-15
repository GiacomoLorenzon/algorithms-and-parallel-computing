//============================================================================
// Name        : Roots.cpp
// Author      : Danilo
// Version     :
// Copyright   :
//============================================================================
//#include <iostream>
//#include <cmath>
//#include <cstdlib>
//#include <vector>


#include "rootfinding.h"
#include "Function.h"
#include "Bisection.h"
#include "Newton.h"
#include "Robust.h"

using std::vector;
using std::cout;
using std::endl;

int main() {

	  int nit_bis;
	  int nit_newt;
	  /*
	    vector<double> coeffs;

	    coeffs.push_back(-0.5);
	    coeffs.push_back(0);
	    coeffs.push_back(1.0);
	  */

	  Function f({-0.5, 0., 1.});// x^2 - 1/2!

	  Bisection bis(f,0., 1., 1e-8, INCREMENT, 100);
	  cout << "Bisection"<<endl;
	  cout << bis.find_root(nit_bis);

	  cout << '\t' << nit_bis << endl;

	  Newton nw(f, .1, 1e-8, INCREMENT, 100);

	  cout << "Newton"<<endl;
	  cout << nw.find_root(nit_newt);
	  cout << '\t' << nit_newt << endl;

	  Robust rob(f,0., 1., 1e-8, 1e4, INCREMENT, 100);
	  cout << "Robust"<<endl;
	  cout << rob.find_root(nit_bis,nit_newt);
	  cout << '\t' << nit_bis
	       << " "  << nit_newt << endl;

	  return 0;
}
