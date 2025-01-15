#ifndef GET_HH
#define GET_HH
#include <mpi.h>
#include <vector>
#include <string>
#include <iostream>
#include <limits>
#include <cmath>

namespace get
{
  void read_pn (unsigned int & p, unsigned int & n);

  std::vector<double> read_vector (unsigned int & n, MPI_Comm const & comm);
}

#endif
