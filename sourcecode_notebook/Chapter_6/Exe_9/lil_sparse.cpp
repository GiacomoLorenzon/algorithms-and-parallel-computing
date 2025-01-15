#include "lil_sparse.hpp"

namespace numeric
{ 
  lil_sparse::lil_sparse (size_type rows, size_type columns)
    : nonzero (rows), m_rows (rows), m_columns (columns) {}

  lil_sparse::inner_iterator
  lil_sparse::search (size_type i, size_type j)
  {
    inner_iterator it = nonzero[i].begin ();
    while (it != nonzero[i].end () && it -> first < j) ++it;
    return it;
  }
  
  lil_sparse::const_inner_iterator
  lil_sparse::search (size_type i, size_type j) const
  {
    const_inner_iterator it = nonzero[i].cbegin ();
    while (it != nonzero[i].cend () && it -> first < j) ++it;
    return it;
  }
  
  void
  lil_sparse::set (size_type i, size_type j, value_type a)
  {
    inner_iterator it = search (i, j);
    if (it != nonzero[i].end () && it -> first == j)
      {
        it -> second = a;
      }
    else
      {
        nonzero[i].insert (it, std::make_pair (j, a));
      }
  }

  lil_sparse::value_type
  lil_sparse::get (size_type i, size_type j) const
  {
    // If you can't find an entry in nonzero, then it's zero.
    value_type result = 0.;
    const_inner_iterator it = search (i, j);
    if (it != nonzero[i].cend () && it -> first == j)
      {
        result = it -> second;
      }
    return result;
  }  
  
}
