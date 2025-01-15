#ifndef OPERATION_HH
#define OPERATION_HH
#include <vector>
#include <cmath>

namespace operation
{
  double partial_max_module(std::vector<double> & v);

  double partial_sum (const unsigned int & p, std::vector<double> & v);
}

#endif
