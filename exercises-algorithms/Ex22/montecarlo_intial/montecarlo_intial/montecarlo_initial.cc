#include <mpi.h>
#include <random>

#include "montecarlo.hh"

namespace quadrature
{
  std::pair<double, double>
  montecarlo (const std::function<double (double)> & f, unsigned long N)
  {
    int rank, size;
    MPI_Comm_rank (MPI_COMM_WORLD, &rank);
    MPI_Comm_size (MPI_COMM_WORLD, &size);

    // your code goes here
    
  }
}
