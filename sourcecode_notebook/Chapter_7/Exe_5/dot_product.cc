#include <iostream>
#include <mpi.h>
#include <numeric>
#include <vector>

int
main (int argc, char *argv[])
{
  MPI_Init (&argc, &argv);

  int rank, size;
  MPI_Comm_rank (MPI_COMM_WORLD, &rank);
  MPI_Comm_size (MPI_COMM_WORLD, &size);

  std::vector<double> x, y;

  if (rank == 0)
    {
      unsigned long dimensions = 0;
      std::cin >> dimensions;

      unsigned long counter = 0;
      double value;
      while (std::cin >> value)
        {
          if (counter++ < dimensions) x.push_back (value);
          else y.push_back (value);
        }
    }

  if (x.size () != y.size ())
    {
      std::cerr << "Wrong input vectors, dimension mismatch" << std::endl;
    }
  else
    {
      unsigned long aux_dimension = x.size ();
      while (aux_dimension % size != 0) ++aux_dimension;
      // The 0s added by resize do not affect the result
      x.resize (aux_dimension);
      y.resize (aux_dimension);

      unsigned long portion = aux_dimension / size;
      MPI_Bcast (&portion, 1, MPI_UNSIGNED_LONG, 0, MPI_COMM_WORLD);

      std::vector<double> local_x (portion), local_y (portion);
      MPI_Scatter (x.data (), portion, MPI_DOUBLE,
                   local_x.data (), portion, MPI_DOUBLE,
                   0, MPI_COMM_WORLD);
      MPI_Scatter (y.data (), portion, MPI_DOUBLE,
                   local_y.data (), portion, MPI_DOUBLE,
                   0, MPI_COMM_WORLD);

      const double partial = std::inner_product (local_x.cbegin (),
                                                 local_x.cend (),
                                                 local_y.cbegin (),
                                                 0.0);
      double product;
      MPI_Reduce (&partial, &product, 1, MPI_DOUBLE,
                  MPI_SUM, 0, MPI_COMM_WORLD);

      if (rank == 0)
        {
          std::cout << product << std::endl;
        }
    }

  MPI_Finalize ();
  return 0;
}
