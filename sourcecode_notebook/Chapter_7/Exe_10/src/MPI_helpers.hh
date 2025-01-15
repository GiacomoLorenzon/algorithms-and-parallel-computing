#ifndef __WORD_COUNTING_MPI_HELPERS__
#define __WORD_COUNTING_MPI_HELPERS__

#include <utility>

namespace mpi
{
  int
  rank (void);

  int
  size (void);

  std::pair<char, char>
  get_processor_bounds (unsigned);
}

#endif // __WORD_COUNTING_MPI_HELPERS__
