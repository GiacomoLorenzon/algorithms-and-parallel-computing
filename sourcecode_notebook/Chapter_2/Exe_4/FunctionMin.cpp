#include <algorithm>
#include <cmath>
#include <random>

#include "FunctionMin.hpp"

//gradient descent with x_init initial point
double FunctionMin::solve (double x_init) const
{
  Function df = f.derivative();
  double x0 = x_init;
  double f0 = f.eval (x0);
  bool converged = ((sup_limit - inf_limit) < tolerance
                    || std::abs (df.eval (x0)) < tolerance);
  unsigned int i;

  for (i = 0; i < max_iterations && ! converged; ++i)
    {
      const double deriv = df.eval (x0);
      double x1 = x0 - deriv * step;

      if (deriv > 0)
        x1 = std::max (inf_limit, x1);
      else
        x1 = std::min (sup_limit, x1);

      const double f1 = f.eval (x1);
      converged = (std::abs (f1 - f0) < tolerance
                   || std::abs (df.eval (x1)) < tolerance);

      x0 = x1;
      f0 = f1;
    }

  return x0;
}

// gradient descent
double FunctionMin::solve (void) const
{
  return solve ((sup_limit + inf_limit) / 2);
}

// gradient descent with multi-start
double FunctionMin::solve_multistart (unsigned int n_trials) const
{
  std::default_random_engine generator;
  std::uniform_real_distribution<double> distribution (inf_limit,
                                                       sup_limit);
  double x_min = solve ();

  for (unsigned int n = 1; n < n_trials; ++n)
    {
      const double x_guess = distribution (generator);
      const double x_new = solve (x_guess);

      if (f.eval (x_new) < f.eval (x_min))
        x_min = x_new;
    }

  return x_min;
}

// gradient descent with multi-start and domain decomposition
double FunctionMin::solve_domain_decomposition (unsigned n_intervals,
                                                unsigned n_trials) const
{
  const double internal_step = (sup_limit - inf_limit) / n_intervals;
  double internal_inf_limit = inf_limit;
  double x_min = inf_limit;

  for (unsigned int i = 1; i <= n_intervals; ++i)
    {
      //That's inefficient!! Think how to improve this!
      FunctionMin minf_int (f, internal_inf_limit,
                            internal_inf_limit + internal_step,
                            tolerance,
                            step, max_iterations);
      const double x_iter = minf_int.solve_multistart (n_trials);

      if (f.eval (x_iter) < f.eval (x_min))
        x_min = x_iter;

      internal_inf_limit += internal_step;
    }

  return x_min;
}
