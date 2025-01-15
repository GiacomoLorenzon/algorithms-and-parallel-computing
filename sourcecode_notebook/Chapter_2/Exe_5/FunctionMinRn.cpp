#include <cmath>
#include <iostream>
#include <random>

#include "FunctionMinRn.h"
#include "FunctionRn.h"
#include "Monomial.h"

Point FunctionMinRn::solve (const Point & P) const
{
  if (debug)
    {
      for (double ii: inf_limits)
        std::cout << ii << " ";
      std::cout << std::endl;

      for (double ss: sup_limits)
        std::cout << ss << " ";
      std::cout << std::endl;
    }

  Point P0 (P.get_coords());
  double f0 = f.eval (P0);
  bool converged = false;

  if (debug)
    std::cout << "Starting gradient" << std::endl;

  for (unsigned int iter = 0;
       iter < max_iterations && ! converged; ++iter)
    {
      if (debug)
        {
          std::cout << "P0: ";
          P0.print ();
        }

      for (std::size_t j = 0; j < P0.get_n_dimensions (); ++j)
        {
          const double grad_j = f.eval_deriv (j, P0);
          debug_info ("grad_j", grad_j);
          double new_x = P0.get_coord (j) - grad_j * step;
          debug_info ("new_x", new_x);

          if (grad_j > 0)
            new_x = std::max (inf_limits[j], new_x);
          else
            new_x = std::min (sup_limits[j], new_x);

          debug_info ("new_x", new_x);
          P0.set_coord (j, new_x);

          if (debug)
            {
              P0.print();
            }
        }

      //compute function in the new point
      const double f1 = f.eval (P0);
      debug_info ("f1", f1);

      //update gradient in the new point
      const Point grad = compute_gradient (P0);

      if (debug)
        {
          std::cout << "grad" << std::endl;
          grad.print ();
        }

      debug_info ("delta f", std::abs (f1 - f0));
      debug_info ("infinity_norm", grad.infinity_norm ());
      converged = (std::abs (f1 - f0) < tolerance)
        || (grad.infinity_norm () < tolerance);

      f0 = f1;
    }

  return P0;
}

Point FunctionMinRn::solve (void) const
{
  std::vector<double> initial_coords;

  //compute domain mid point
  for (std::size_t i = 0; i < sup_limits.size (); ++i)
    initial_coords.push_back ((sup_limits[i] + inf_limits[i]) / 2);
  const Point P (initial_coords);

  return solve (P);
}

// gradient descent with multi-start
Point FunctionMinRn::solve_multistart (unsigned int n_trials) const
{
  std::default_random_engine generator;
  std::uniform_real_distribution<double> distribution (0, 1);
  std::vector<double> random_coords;
  debug_info ("Running multi-start");

  //generate random coords
  for (std::size_t i = 0; i < inf_limits.size (); ++i)
    {
      debug_info ("Pick random value");
      const double rand_val = distribution (generator);
      random_coords.push_back (inf_limits[i] +
                               (sup_limits[i] - inf_limits[i])
                               * rand_val);
    }

  if (debug)
    {
      for (double rc: random_coords)
        std::cout << rc << " ";
      std::cout << std::endl;
    }

  debug_info ("Creating random point");
  Point random_point = Point (random_coords);

  if (debug)
    {
      std::cout << "First random point" << std::endl;
      random_point.print ();
    }

  Point p_min = solve (random_point);
  debug_info ("First random point val", f.eval (p_min));

  for (unsigned n = 1; n < n_trials; ++n)
    {
      //generate random coords
      for (std::size_t i = 0; i < inf_limits.size (); ++i)
        random_coords[i] = inf_limits[i] +
          (sup_limits[i] - inf_limits[i]) * distribution (generator);

      random_point = Point (random_coords);
      const Point p_new = solve (random_point);
      debug_info ("Local optimum found: ", f.eval (p_new));

      if (f.eval (p_new) < f.eval (p_min))
        p_min = p_new;
    }

  return p_min;
}

// gradient descent with multi-start and domain decomposition
Point FunctionMinRn::solve_domain_decomposition (unsigned int n_intervals,
                                                 unsigned int n_trials) const
{
  std::vector<double> internal_steps;
  // compute steps along each axis
  for (std::size_t i = 0; i < inf_limits.size(); ++i)
    internal_steps.push_back ((sup_limits[i] - inf_limits[i]) / n_intervals);

  debug_info ("Temp minimum");
  Point p_min = Point (inf_limits);

  if (debug)
    p_min.print ();

  const unsigned int n_subspaces = pow (n_intervals, inf_limits.size ());
  debug_info ("N subspaces :", n_subspaces);

  std::vector<double> cur_inf_limit (inf_limits);
  for (unsigned int i = 1; i <= n_subspaces; ++i)
    {
      // compute cur_sup_limits
      debug_info ("compute cur_sup_limits");
      std::vector<double> cur_sup_limit;
      for (std::size_t j = 0; j < cur_inf_limit.size (); ++j)
        cur_sup_limit.push_back (cur_inf_limit[j] + internal_steps[j]);

      debug_info ("Create local solver");
      //That's inefficient!! Think how to improve this!
      FunctionMinRn minf_int (f,  tolerance,  step, max_iterations,
                              cur_inf_limit, cur_sup_limit);

      if (debug)
        {
          std::cout << "Inf intervals" << std::endl;
          for (double elem: cur_inf_limit)
            std::cout << elem << " ";
          std::cout << std::endl;

          std::cout << "Sup intervals" << std::endl;
          for (double elem: cur_sup_limit)
            std::cout << elem << " ";
          std::cout << std::endl;
        }

      debug_info ("Compute new minimum");
      const Point p_iter = minf_int.solve_multistart (n_trials);

      if (debug)
        p_iter.print ();

      if (f.eval (p_iter) < f.eval (p_min))
        p_min = p_iter;

      debug_info ("Compute next sub-interval");
      next_inf_limit (cur_inf_limit, internal_steps);
    }

  return p_min;
}

void FunctionMinRn::next_inf_limit (std::vector<double> & cur_inf_limit,
                                    const std::vector<double> & internal_steps) const
{
  for (std::size_t j = 0; j < cur_inf_limit.size (); ++j)
    {
      if (cur_inf_limit[j] + internal_steps[j] >= sup_limits[j])
        {
          cur_inf_limit[j] = inf_limits[j];
          debug_info ("Updating dimension: ", j);
          debug_info ("New inf limit: ", cur_inf_limit[j]);
        }
      else
        {
          cur_inf_limit[j] += internal_steps[j];
          debug_info ("Updating dimension: ", j);
          debug_info ("New inf limit: ", cur_inf_limit[j]);
          return;
        }
    }
}


Point FunctionMinRn::compute_gradient (const Point & P0) const
{
  std::vector<double> grad;

  for (std::size_t j = 0; j < P0.get_n_dimensions (); ++j)
    grad.push_back (f.eval_deriv (j, P0));

  return Point (grad);
}

void FunctionMinRn::debug_info (const std::string& s) const
{
  if (debug)
    std::cout << s << " " << std::endl;
}

void FunctionMinRn::debug_info (const std::string& s, double val) const
{
  if (debug)
    std::cout << s << " " << val << std::endl;
}
