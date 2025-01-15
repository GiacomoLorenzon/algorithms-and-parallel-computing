#include "operation.hh"

namespace operation
{
  double partial_max_module(std::vector<double> & v)
  {
    double n=0;
    double m=0;
    for (unsigned int i=0; i<v.size(); i++)
    {
      n=std::abs(v[i]);
      if (n>m)
        m=n;
    }
    return m;
  }

  double partial_sum (const unsigned int & p, std::vector<double> & v)
  {
    double n=0.0;
    double m=0.0;
    for ( unsigned int i=0; i<v.size(); i++)
    {
      m=std::abs(v[i]);
      n += pow(m,p);
    }
    return n;
  }

}
