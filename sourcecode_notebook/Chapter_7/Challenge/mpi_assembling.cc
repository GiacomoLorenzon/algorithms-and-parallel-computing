#include <mpi.h>

#include "mpi_assembling.hh"

namespace mpi_assembling
{
  double max (double local)
  {
    double total(0.);
    //Store the result -apply MPI_MAX to the portions of data in local- on all 
    //the processes
    MPI_Allreduce (&local, &total, 1, MPI_DOUBLE, MPI_MAX, MPI_COMM_WORLD);
    return total;
  }

  double sum_power (double local, const unsigned int & p)
  {
    int rank;
    MPI_Comm_rank (MPI_COMM_WORLD, &rank);

    double total (0.);
    double a=(1.0)/p;
    //Store the result -apply MPI_SUM to the portions of data in local- on all
    //the processes
    MPI_Allreduce (&local, &total, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

    double totalfinal = pow(total, a);

    return totalfinal;
  }

}
