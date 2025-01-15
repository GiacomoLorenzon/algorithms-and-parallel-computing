#ifndef MPI_ASSEMBLING_HH
#define MPI_ASEEMBLING_HH

#include <ostream>
#include <cmath>

namespace mpi_assembling
{
  double max (double local);

  double sum_power (double local,const unsigned int & p);
}

#endif
