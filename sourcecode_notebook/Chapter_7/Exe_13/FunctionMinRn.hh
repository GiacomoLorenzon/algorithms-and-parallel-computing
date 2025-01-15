#ifndef FUNCTIONMINRN_H_
#define FUNCTIONMINRN_H_

#include <string>
#include <vector>

#include "FunctionRn.hh"
#include "Point.hh"

class FunctionMinRn
{
  static constexpr bool debug = false;

  FunctionRn f;

  double tolerance;
  double step;
  unsigned int max_iterations;

  std::vector<double> inf_limits;
  std::vector<double> sup_limits;

  Point compute_gradient (const Point & P0) const;

  void debug_info (std::string const& s) const;

  void debug_info (std::string const& s1, double val) const;

  // use P as starting point
  Point solve (const Point & P) const;

  // for multi start implementation
  std::vector<double>
  next_inf_limit (unsigned iteration, unsigned intervals,
                  const std::vector<double> & internal_steps) const;

public:
  FunctionMinRn (FunctionRn func, double tol, double s,
                 unsigned int max_it,
                 const std::vector<double> & inff_limits,
                 const std::vector<double> & supp_limits)
    : f (func), tolerance (tol), step (s), max_iterations (max_it),
      inf_limits (inff_limits), sup_limits (supp_limits) {}

  // gradient descent
  Point solve (void) const;

  // gradient descent with multi-start
  Point solve_multistart (unsigned int n_trials) const;

  // gradient descent with multi-start and domain decomposition
  Point solve_domain_decomposition (unsigned int n_intervals,
                                    unsigned int n_trials) const;
};

#endif /* FUNCTIONMINRN_H_ */
