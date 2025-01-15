#include <cmath>
#include <iostream>
#include <mpi.h>

#include "gradient.hh"
#include "mpi_helpers.hh"
#include "nd_vector.hh"

double
my_function (const numeric::nd_vector &);

int
main (int argc, char *argv[])
{
  MPI_Init (&argc, &argv);

  const unsigned rank = mpi::rank ();

  numeric::nd_vector x {1., 1.};
  const numeric::nd_vector gradient =
    numeric::compute_gradient (my_function, x);
  if (rank == 0)
    {
      for (numeric::nd_vector::size_type i = 0;
           i < gradient.size (); ++i)
        {
          std::cout << gradient[i] << std::endl;
        }
    }

  MPI_Finalize ();
  return 0;
}

double
my_function (const numeric::nd_vector & x)
{
  return x[0] * x[0] + x[1];
}
