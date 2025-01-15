#ifndef FUNCTIONRN_H_
#define FUNCTIONRN_H_

#include <vector>

#include "Monomial.hh"
#include "Point.hh"

class FunctionRn
{
  std::vector<Monomial> monoms;

  static constexpr double h = 1e-5;

public:
  double eval (const Point & P) const;

  void addMonomial (const Monomial & m);

  //evaluate derivative wrt dim j in P
  double eval_deriv (std::size_t j,
                     const Point & P) const;
};

#endif /* FUNCTIONRN_H_ */
