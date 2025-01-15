#ifndef CALCULATE_HH
#define CALCULATE_HH
#include "operation.hh"
#include "mpi_assembling.hh"
#include <iostream>
#include <mpi.h>
#include <vector>
#include <cmath>

namespace calculate
{
  double calculate_norm(const unsigned int & p, std::vector<double> & v);
}

#endif
