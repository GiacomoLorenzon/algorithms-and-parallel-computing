#include "FunctionRn.h"

double FunctionRn::eval (const Point & P) const
{
  double value = 0;

  for (std::size_t i = 0; i < monoms.size (); ++i)
    value += monoms[i].eval (P);

  return value;
}

void FunctionRn::addMonomial (const Monomial & m)
{
  monoms.push_back (m);
}

//evaluate derivative wrt dim j in P
double FunctionRn::eval_deriv (std::size_t j,
                               const Point & P) const
{
  Point P1 (P.get_coords ());
  Point P2 (P.get_coords ());
  P1.set_coord (j, P.get_coord (j) + h);
  P2.set_coord (j, P.get_coord (j) - h);
  return (eval (P1) - eval (P2)) / (2 * h);
}
