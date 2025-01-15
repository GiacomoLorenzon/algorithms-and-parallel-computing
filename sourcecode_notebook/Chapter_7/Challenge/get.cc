#include "get.hh"

namespace get
{
  void read_pn (unsigned int & p, unsigned int & n)
  {
    int rank;
    MPI_Comm_rank (MPI_COMM_WORLD, &rank);

    if (rank == 0)
    {
      std::cout<<"Please insert p\n"<<std::endl;
      std::cout<<"Assigning 0 to p means that you want to " 
                                    << "calculate infinity norm\n "<<std::endl;
      std::cin >> p;
      if (p==0)
        std::cout<<"Infinity norm selected"<<std::endl;
      else
        std::cout<<"Finite norm selected"<<std::endl;
      std::cout<<"Please insert n"<<std::endl;
      std::cin >> n;
    }

    //Deliver a copy of the data in p and n to all the processes
    MPI_Bcast (&p, 1, MPI_UNSIGNED, 0, MPI_COMM_WORLD);
    MPI_Bcast (&n, 1, MPI_UNSIGNED, 0, MPI_COMM_WORLD);
  }

  std::vector<double> read_vector (unsigned int & n, MPI_Comm const & comm)
  {
    int rank, size;
    MPI_Comm_rank (comm, &rank);
    MPI_Comm_size (comm, &size);

    //It is necessary to declare them in order to be able to calculate 
    //the norm of any vector, independently of its size
    const unsigned local_n = n % size > 0 ? n / size + 1 : n / size;
    const unsigned communication_n = local_n * size;

    //Initialize a new vector of doubles whose size is local_n
    std::vector<double> result (local_n);

    if (rank == 0)
    {
      std::vector<double> input(n);
      std::cout<< "Enter vector"<<"\n";
      for (double & e : input)
        std::cin >> e;
      //Add zeros at the end of the vector input in order to make its length multiple
      //of size without affecting the computation of the norms  
      input.resize (communication_n, 0);

      //Send a portion of the data in input to all the processes storing it in result
      MPI_Scatter (input.data (), local_n, MPI_DOUBLE, result.data (), 
                                                local_n, MPI_DOUBLE, 0, comm);
    }
    else
    {
      MPI_Scatter (nullptr, local_n, MPI_DOUBLE,result.data (), 
                                                local_n, MPI_DOUBLE, 0, comm);
    }

    return result;
  }
}
