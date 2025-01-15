#include <iostream>
#include <random>
#include <mpi.h>

double square(double x); // return x*x

double dboard(unsigned darts, unsigned seed); // implement Pi approximation
                                              // through darts random sampling

int main (int argc, char* argv[])
{
  // init
  MPI_Init(&argc, &argv);

  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  if (argc == 3)
  {
    // get number of iterations and darts from command-line
    unsigned iterations = std::stoul(argv[1]);
    unsigned darts = std::stoul(argv[2]);
    
    // compute local number of iterations
    const unsigned long local_n = iterations / size;
    // initialize local seed
    unsigned local_seed = rank * local_n;

    // compute local sum
    double local_sum = 0;
    for (unsigned i = 1; i <= local_n; ++i)
      local_sum += dboard(darts, local_seed++);

/* INITIAL VERSION
    // MPI-MPI_Reduce in second stage !
    if (rank > 0)
    {
      MPI_Send(&local_sum, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
    }
    else
    {
      double approx_pi = local_sum;


      for (int r = 1; r < size; ++r)
      {
        MPI_Recv(&local_sum, 1, MPI_DOUBLE, r, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        approx_pi += local_sum;
      }

      approx_pi /= iterations;

      std::cout << "Pi approximation " << approx_pi << std::endl;
    }
*/

/*
    ERROR!!!!!! BE CAREFUL WITH VARIABLE SCOPE!!!
    if (rank == 0)
    {
      double sum = 0;
    }

    MPI_Reduce(&local_sum, &sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
*/

    // communication
    if (rank == 0)
    {
      double sum = 0;
      MPI_Reduce(&local_sum, &sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

      double approx_pi = sum / iterations;

      std::cout << "Pi approximation " << approx_pi << std::endl;
    }
    else
      MPI_Reduce(&local_sum, nullptr, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
  }
  else
    if (rank ==0)
      std::cerr << "Error, two arguments expected " << std::endl;

  // finalize
  MPI_Finalize();
  return 0;
}

double square(double x)
{
  return x*x;
}

double dboard(unsigned darts, unsigned seed)
{
  double  x_coord,    // x coordinate, between -1 and 1
          y_coord,    // y coordinate, between -1 and 1
          pi;         // pi approximation
  unsigned score{0};  // number of darts that hit circle

  // random engine generator
  std::default_random_engine generator(seed);

  // callable object for random number generation
  std::uniform_real_distribution<double> distribution (-1.0,1.0);

  for (unsigned n = 1; n <= darts; ++n)
  {
    // generate random values for x and y coordinates
    x_coord = distribution(generator);
    y_coord = distribution(generator);

    // if dart lands in circle, increment score
    if ((square(x_coord) + square(y_coord)) <= 1.0)
      ++score;
  }

  // calculate pi
  pi = 4.0 * static_cast<double>(score) / static_cast<double>(darts);

  return pi;
}
