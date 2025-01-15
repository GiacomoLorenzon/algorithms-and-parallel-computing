#ifndef __MINHEAP__
#define __MINHEAP__

#include <initializer_list>
#include <vector>

namespace ds
{
  class MinHeap
  {
    typedef std::vector<int> container_type;

  public:
    typedef int value_type;
    typedef typename container_type::size_type size_type;

  private:
    container_type m_data;

    void
    sift_down (size_type i);
    void
    sift_up (size_type i);

    void
    build_Heap (void);

    inline size_type
    left (size_type i) const
    {
      return 2 * i + 1;
    }

    inline size_type
    right (size_type i) const
    {
      return 2 * i + 2;
    }

    inline size_type
    parent (size_type i) const
    {
      return (i + 1) / 2 - 1;
    }

  public:
    MinHeap (void) = default;

    MinHeap (container_type::const_iterator first, 
          container_type::const_iterator last);

    MinHeap (std::initializer_list<value_type> il);

    inline size_type
    size (void) const
    {
      return m_data.size ();
    }

    inline bool
    empty (void) const
    {
      return m_data.empty ();
    }

    inline const value_type &
    peek (void) const
    {
      return m_data.front ();
    }

    void
    pop (void);

    void
    push (const value_type &);

    void
    replace (const value_type &);
  
  };

}

#endif
