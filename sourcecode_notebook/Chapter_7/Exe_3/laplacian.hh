#ifndef __LAPLACIAN__
#define __LAPLACIAN__

#include <functional>

#include "nd_vector.hh"

namespace numeric
{
  double
  compute_laplacian (std::function<double (const nd_vector &)>,
                     const nd_vector &, double h = 0.01);
}

#endif
