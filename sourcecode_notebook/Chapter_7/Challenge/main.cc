#include <iostream>
#include <mpi.h>
#include <vector>
#include "get.hh"
#include "calculate.hh"
using namespace std;

int main (int argc, char *argv[])
{
  MPI_Init (&argc, &argv);

  //Initialize size and rank
  int rank, size;
  MPI_Comm_rank (MPI_COMM_WORLD, &rank);
  MPI_Comm_size (MPI_COMM_WORLD, &size);

  unsigned int p;
  unsigned int n;

  //Read from standard input the values of p and n
  //Moreover it delivers a copy of the data in p and n to all the processes
  //through broadcast
  get::read_pn (p, n);

  //Read from standard input the vector v
  //Moreover it sends a portion of the data to all the processes
  //through scatter
  vector<double> v = get::read_vector(n,  MPI_COMM_WORLD);

  //Calculate the p norm of the n-dim. vector v
  double norm = calculate::calculate_norm(p,v);

  //Print the result
  if (rank==0)
  {
    if (p==0)
      cout<<"inf";
    else
      cout<<p;
    cout<<"-norm="<<norm<<endl;
  }

  MPI_Finalize ();

  return 0;
}
