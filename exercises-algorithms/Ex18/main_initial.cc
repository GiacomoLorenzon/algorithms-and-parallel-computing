#include <iostream> 
#include <random> 
#include <mpi.h> 

double square(double x); // return x*x

double dboard(unsigned darts, unsigned seed); // implement Pi approximation 
                                              // through darts random sampling

int main (int argc, char* argv[])
{
  // init

  if (argc == 3)
  {
    // get number of iterations and darts from command-line
    
    // compute local number of iterations
    
    // initialize local seed
    
    // compute local sum

    // communication
    if (rank > 0)
    {
      /*
        int MPI_Send (const void *buf, int count,
                      MPI_Datatype datatype,
                      int dest, int tag,
                      MPI_Comm comm);
      */
    }
    else
    {
        /*
          int MPI_Recv (void *buf, int count,
                        MPI_Datatype datatype,
                        int source, int tag,
                        MPI_Comm comm,
                        MPI_Status *status);
        */

      std::cout << "Pi approximation " << approx_pi << std::endl;
    }
  }
  else
    std::cerr << "Error, two arguments expected " << std::endl;

  // finalize

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

