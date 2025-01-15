#include "calculate.hh"

namespace calculate
{
  double calculate_norm (const unsigned int & p, std::vector<double> & v)
  {
    //Calculating the norm we need to differentiate between finite and infinity norm

    //Infinity norm
    if(p==0)
    {
      const double local = operation::partial_max_module(v);
      double norm = mpi_assembling::max (local);
      return norm;
    }
    //Finite norm
    else
    {
      const double local = operation::partial_sum (p, v);
      double norm= mpi_assembling::sum_power(local, p);
      return norm;
    }
  }
}
