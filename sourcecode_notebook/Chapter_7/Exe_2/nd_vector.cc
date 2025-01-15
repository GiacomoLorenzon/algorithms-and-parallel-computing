#include "nd_vector.hh"

namespace numeric
{
  nd_vector::nd_vector (size_type n)
    : x (n, 0.) {}

  nd_vector::nd_vector (std::initializer_list<double> il)
    : x (il) {}

  nd_vector::size_type
  nd_vector::size (void) const
  {
    return x.size ();
  }

  nd_vector::reference
  nd_vector::operator [] (size_type idx)
  {
    return x[idx];
  }

  nd_vector::value_type
  nd_vector::operator [] (size_type idx) const
  {
    return x[idx];
  }

  nd_vector::pointer
  nd_vector::data (void)
  {
    return x.data ();
  }

  nd_vector::const_pointer
  nd_vector::data (void) const
  {
    return x.data ();
  }
}
