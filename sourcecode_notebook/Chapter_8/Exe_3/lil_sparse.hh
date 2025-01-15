#ifndef __LIL_SPARSE__
#define __LIL_SPARSE__

#include <list>
#include <utility>
#include <vector>

namespace numeric
{
  template <typename T>
  class lil_sparse
  {  
  public:
    typedef T value_type;
    typedef std::size_t size_type;
    
  private:  
    typedef std::list<
      std::pair<const std::size_t, value_type>> inner_list;
    typedef typename inner_list::iterator inner_iterator;
    typedef typename inner_list::const_iterator const_inner_iterator;
    typedef std::vector<inner_list> data_structure;

    data_structure nonzero;

    size_type m_rows;
    size_type m_columns;

    inner_iterator
    search (size_type, size_type);
    const_inner_iterator
    search (size_type, size_type) const;

  public:
    explicit lil_sparse (size_type rows = 1,
                         size_type columns = 0);

    size_type
    rows (void) const {return m_rows;}
    size_type
    columns (void) const {return m_columns;}

    void
    set (size_type, size_type, value_type);

    value_type
    get (size_type, size_type) const;
    
  };  /* end of class declaration */
  
  template <typename T>
  lil_sparse<T>::lil_sparse (size_type rows, size_type columns)
    : nonzero (rows), m_rows (rows), m_columns (columns) {}

  template <typename T>
  typename lil_sparse<T>::inner_iterator
  lil_sparse<T>::search (size_type i, size_type j)
  {
    inner_iterator it = nonzero[i].begin ();
    while (it != nonzero[i].end () && it -> first < j) ++it;
    return it;
  }
  
  template <typename T>
  typename lil_sparse<T>::const_inner_iterator
  lil_sparse<T>::search (size_type i, size_type j) const
  {
    const_inner_iterator it = nonzero[i].cbegin ();
    while (it != nonzero[i].cend () && it -> first < j) ++it;
    return it;
  }
  
  template <typename T>
  void
  lil_sparse<T>::set (size_type i, size_type j, value_type a)
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

  template <typename T>
  typename lil_sparse<T>::value_type
  lil_sparse<T>::get (size_type i, size_type j) const
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

#endif
