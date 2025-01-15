#ifndef __GRADIENT__
#define __GRADIENT__

#include <functional>

#include "nd_vector.hh"

namespace numeric
{
  nd_vector
  compute_gradient (std::function<double (const nd_vector &)>,
                    const nd_vector &, double h = 0.01);
}

#endif
