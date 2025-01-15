#include <mpi.h>

#include "laplacian.hh"

namespace numeric
{
  double
  compute_laplacian (std::function<double (const nd_vector &)> f,
                     const nd_vector & x, double h)
  {
    double laplacian (0.);
    const double h2 = h * h;

    int rank, size;
    MPI_Comm_rank (MPI_COMM_WORLD, &rank);
    MPI_Comm_size (MPI_COMM_WORLD, &size);

    for (nd_vector::size_type i = rank; i < x.size (); i += size)
      {
        nd_vector x_plus_h (x), x_minus_h (x);
        x_plus_h[i] += h;
        x_minus_h[i] -= h;
        laplacian += (f (x_plus_h) - 2 * f (x) + f (x_minus_h)) / h2;
      }

    MPI_Allreduce (MPI_IN_PLACE, &laplacian, 1, MPI_DOUBLE,
                   MPI_SUM, MPI_COMM_WORLD);

    return laplacian;
  }
}
