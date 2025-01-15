#ifndef __KMEANS_MPI_HH__
#define __KMEANS_MPI_HH__

#include <ostream>
#include <mpi.h>
#include <string>

namespace mpi
{
  int rank (MPI_Comm const&);

  int size (MPI_Comm const&);

  void tidy_output (std::ostream &, std::string const&, MPI_Comm const&);
}

#endif // __KMEANS_MPI_HH__
