#ifndef __LIL_SPARSE__
#define __LIL_SPARSE__

#include <list>
#include <utility>
#include <vector>

namespace numeric
{
  class lil_sparse
  {  
  public:
    typedef double value_type;
    typedef std::size_t size_type;
    
  private:  
    typedef std::list<
      std::pair<const std::size_t, value_type>> inner_list;
    typedef inner_list::iterator inner_iterator;
    typedef inner_list::const_iterator const_inner_iterator;
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
  
}

#endif
