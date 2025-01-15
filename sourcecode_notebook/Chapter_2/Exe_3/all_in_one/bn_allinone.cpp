/*!
 * \file bn-allinone.cpp
 * \brief all the exercise code in a single file. Original version by Luca Formaggia
 * \date Oct 14, 2016
 */

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <limits>

//! Type for real numbers
typedef double real;

//! Type for convergence check
enum checkT {
  INCREMENT, //! Check the difference between subsequent iterates
  RESIDUAL,  //! Check the residual
  BOTH       //! Check both conditions
};

//! Function f(x)
real f (real x) {
  return pow(x,2) - 0.5;
}

//! First derivative of function f(x) 
real df (real x) {
  return 2. * x;
}

bool converged (real increment, real residual,
        real tol, const checkT& check){
  /*
    Compares a parameter value against desired tolerance.
    The parameter is chosen upon the value of check.
  */
  switch(check){
  case INCREMENT:
      return (increment < tol);
  case RESIDUAL:
      return (residual < tol);
  case BOTH:
      return ((increment < tol)&&(residual < tol));
  default:
      return false;
  }
}

// BISECTION METHOD
real bisection (real a,  real b,
           real tol, int maxit,
           const checkT& check, int& nit)
{
    real u = f(a);  // Evaluate f on boundary a
    real l = b - a; // Interval length
    real r;         // Residual
    real c = a+l;   // Middle point

    nit = 0;
    r = f(c);

    if (u*f(b)>=0.0) {
    std::cout<<"Error Function has same sign at both endpoints"<<std::endl;
    return - std::numeric_limits<double>::infinity();
    }

    while ( !(converged(fabs(l), fabs(r), tol, check))
            && (nit <= maxit) ) {
     /*
      If f(c)f(a) < 0 then the new "right" boundary is c;
      otherwise move the "left" boundary

      The expression
         test ? stat1 : stat2
      means
         if(test)
            stat1
         else
            stat2
    */
        (u*r < 0.) ? (b = c) : (a = c, u = r);
        l *= 0.5;
        c = a + l;
        r = f(c);
        ++nit;
    }
    return c;
}


// NEWTON METHOD
real newton (real xp, real tol, int maxit,
        const checkT& check, int & nit)
{
  real v = f(xp);
  real xnew;

  nit = 0;
  for(int k = 1; k <= maxit; ++k,++nit) {
    double derv = df(xp);
    if(!derv) {
      std::cerr << "ERROR: Division by 0 occurred in Newton algorithm"
        << std::endl;
      exit(1);
    }

    xnew = xp - v / derv;
    v = f(xnew);
    if(converged(fabs(xnew - xp), fabs(v),tol,check)) break;
    xp = xnew;
  }
  return xnew;
}



// ROBUST METHOD
real robust(real a, real b,
        real tol, real cfratio,
        int maxit, const checkT& check,
        int& nit_coarse, int& nit_fine)
{
  // Call bisection method (with a greater desired tolerance)
  real tol_bis = cfratio * tol;
  real x_bis = bisection(a, b, tol_bis, maxit, check, nit_coarse);

  /*
    Call a Newton algorithm which uses as an initial value
    the solution given by bisection method
  */
  return newton(x_bis, tol, maxit, check, nit_fine);
}



// MAIN FUNCTION
int main() {

  int nit_bis;
  int nit_newt;
  std::cout <<  std::numeric_limits<double>::infinity() << std::endl;
  std::cout << "Bisection"<< std::endl;
  std::cout << bisection(0., 1., 1e-8, 100, INCREMENT, nit_bis);
  std::cout << '\t' << nit_bis << std::endl;

  std::cout << "Newton"<< std::endl;
  std::cout << newton(.1, 1e-8, 100, INCREMENT, nit_newt);
  std::cout << '\t' << nit_newt << std::endl;

  std::cout << "Robust"<< std::endl;
  std::cout << robust(0., 1., 1e-8, 1e4, 100, INCREMENT, nit_bis, nit_newt);
  std::cout << '\t' << nit_bis << " "  << nit_newt << std::endl;

  return 0;
}
