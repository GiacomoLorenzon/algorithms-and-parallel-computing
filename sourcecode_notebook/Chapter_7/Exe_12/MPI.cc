#include <vector>

#include "MPI.hh"

namespace mpi
{
  int
  rank (MPI_Comm const& comm)
  {
    int r;
    MPI_Comm_rank (comm, &r);
    return r;
  }

  int
  size (MPI_Comm const& comm)
  {
    int s;
    MPI_Comm_size (comm, &s);
    return s;
  }

  void
  tidy_output (std::ostream & os, std::string const& text, MPI_Comm const& comm)
  {
    const unsigned rk = rank (comm);
    const unsigned sz = size (comm);

    if (rk > 0)
      {
        const unsigned length = text.size ();
        MPI_Send (&length, 1, MPI_UNSIGNED, 0, 0, comm);
        MPI_Send (&text[0], length, MPI_CHAR, 0, 0, comm);
      }
    else
      {
        os << text;

        for (unsigned i = 1; i < sz; ++i)
          {
            unsigned length = 0;
            MPI_Recv (&length, 1, MPI_UNSIGNED, i, 0, comm, 
                                                MPI_STATUS_IGNORE);
            std::string more_text (length, '\0');
            MPI_Recv (&more_text[0], length, MPI_CHAR,
                      i, 0, comm, MPI_STATUS_IGNORE);
            os << more_text;
          }
      }
  }
}
