#ifndef __MONTECARLO__
#define __MONTECARLO__

#include <functional>
#include <utility>

namespace quadrature
{
  std::pair<double, double>
  montecarlo (const std::function<double (double)> & f, unsigned long N);
}

#endif // __MONTECARLO__
