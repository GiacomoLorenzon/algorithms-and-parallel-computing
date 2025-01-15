#include <iostream>

#include "Clustering.hh"
#include "MPI.hh"

int
main (int argc, char * argv[])
{
  MPI_Init (&argc, &argv);

  unsigned dimensions, points, clusters, iterations;
  dimensions = points = clusters = iterations = 0;

  const unsigned rank = mpi::rank (MPI_COMM_WORLD);

  if (rank == 0)
    {
      std::cin >> dimensions >> points >> clusters >> iterations;
    }

  Clustering c (dimensions, points, clusters, iterations);

  mpi::tidy_output (std::cout, c.print (), MPI_COMM_WORLD);

  const unsigned iter = c.calc_cluster ();

  if (rank == 0)
    {
      std::cout << "Number of iterations: " << iter << "\n";
    }

  mpi::tidy_output (std::cout, c.print_labels (), MPI_COMM_WORLD);
  mpi::tidy_output (std::cout, c.print (), MPI_COMM_WORLD);

  MPI_Finalize ();

  return 0;
}
