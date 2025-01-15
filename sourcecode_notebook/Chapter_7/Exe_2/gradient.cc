#include <mpi.h>

#include "gradient.hh"
#include "mpi_helpers.hh"

namespace numeric
{
  nd_vector
  compute_gradient (std::function<double (const nd_vector &)> f,
                    const nd_vector & x, double h)
  {
    nd_vector gradient (x.size ());

    const unsigned rank = mpi::rank (), size = mpi::size ();

    for (nd_vector::size_type i = rank; i < x.size (); i += size)
      {
        nd_vector x_plus_h (x), x_minus_h (x);
        x_plus_h[i] += h;
        x_minus_h[i] -= h;
        gradient[i] = (f (x_plus_h) - f (x_minus_h)) / 2 / h;
      }

    for (nd_vector::size_type i = 0; i < gradient.size (); ++i)
      {
        MPI_Bcast (&gradient[i], 1, MPI_DOUBLE, i % size, MPI_COMM_WORLD);
      }

    return gradient;
  }
}
