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

    MPI_Bcast (&N, 1, MPI_UNSIGNED_LONG, 0, MPI_COMM_WORLD);
    const unsigned long local = N / size;
    const unsigned long subsample = (rank < N % size) ? local + 1 : local;

    std::default_random_engine engine (rank * rank * size * size);
    std::uniform_real_distribution<double> distro (-1., 1.);

    double mean = 0.;
    std::vector<double> ys (subsample);
    for (double & y: ys)
      {
        const double x = distro (engine);
        y = f (x);
        mean += y;
      }
    MPI_Allreduce (MPI_IN_PLACE, &mean, 1, MPI_DOUBLE,
                   MPI_SUM, MPI_COMM_WORLD);
    mean /= N;

    double variance = 0.;
    for (double y: ys) variance += (y - mean) * (y - mean);
    MPI_Allreduce (MPI_IN_PLACE, &variance, 1, MPI_DOUBLE,
                   MPI_SUM, MPI_COMM_WORLD);
    variance /= (N - 1);

    const double integral = 2 * mean;
    const double integral_variance = 2 * 2 * variance / N;

    return std::make_pair (integral, integral_variance);
  }
}
