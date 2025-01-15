#include <mpi.h>
#include <random>

#include "montecarlo.hh"

namespace quadrature {
    std::pair<double, double>
    montecarlo(const std::function<double(double)> &f, unsigned long N) {
        int rank, size;
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        MPI_Comm_size(MPI_COMM_WORLD, &size);

        // N is know only to rank 0; we need to send it everywhere
        MPI_Bcast(&N, 1, MPI_UNSIGNED_LONG, 0, MPI_COMM_WORLD);

        // generate N numbers
        unsigned long local_N = N / size;
        local_N = (rank < N % size) ? local_N + 1 : local_N;

        std::default_random_engine engine(rank * rank * size * size);
        std::uniform_real_distribution<double> distr(-1.0, 1.0);

        double mean = 0;
        std::vector<double> ys(local_N);
        for (double &y: ys) {
            double x = distr(engine);
            y = f(x);
            mean += y;
        }

        MPI_Allreduce(MPI_IN_PLACE, &mean, 1, MPI_DOUBLE,
                      MPI_SUM, MPI_COMM_WORLD);
        mean /= N;

        double variance = 0.;
        for (double y: ys)
            variance += (y - mean) * (y - mean);

        MPI_Allreduce(MPI_IN_PLACE, &variance, 1, MPI_DOUBLE,
                      MPI_SUM, MPI_COMM_WORLD);
        variance /= (N - 1);

        double integral = 2 * mean;
        double integral_variance = 2 * 2 * variance / N;

        return {integral, integral_variance};
    }
}