#include <mpi.h>

#include "MPI_helpers.hh"

namespace mpi
{
  int
  rank (void)
  {
    int rk;
    MPI_Comm_rank (MPI_COMM_WORLD, &rk);
    return rk;
  }

  int
  size (void)
  {
    int sz;
    MPI_Comm_size (MPI_COMM_WORLD, &sz);
    return sz;
  }

  std::pair<char, char>
  get_processor_bounds (unsigned rk)
  {
    constexpr unsigned letters = 26;
    const unsigned sz = size ();
    const unsigned portion = letters / sz;
    unsigned first, second;
    if (rk < letters % sz)
      {
        first = rk * (portion + 1);
        second = first + portion + 1;
      }
    else
      {
        first = (letters % sz) * (portion + 1) +
          (rk - letters % sz) * portion;
        second = first + portion;
      }
    return std::make_pair ('a' + first, 'a' + second);
  }
}
