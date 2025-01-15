#include "minHeap.hpp"

namespace ds
{
  void
  MinHeap::sift_down (size_type i)
  {
    bool keep_sifting = true;

    while (keep_sifting and i < m_data.size ())
      {
        keep_sifting = false;

        const size_type l = left (i), r = right (i);
        size_type best = i;

        if (l < m_data.size () and m_data[l] < m_data[best])
          {
            best = l;
            keep_sifting = true;
          }

        if (r < m_data.size () and m_data[r] < m_data[best])
          {
            best = r;
            keep_sifting = true;
          }

        if (keep_sifting)
          {
            using std::swap;
            swap (m_data[best], m_data[i]);
            i = best;
          }
      }
  }

  void
  MinHeap::sift_up (size_type i)
  {
    while (i > 0 and m_data[i] < m_data[parent (i)])
      {
        using std::swap;
        swap (m_data[i], m_data[parent (i)]);
        i = parent (i);
      }
  }

  void
  MinHeap::build_Heap (void)
  {
    for (size_type i = parent (m_data.size ());
         i >= 0 and i < m_data.size (); --i)
      {
        sift_down (i);
      }
  }

  MinHeap::MinHeap (container_type::const_iterator first, 
              container_type::const_iterator last)
    : m_data (first, last)
  {
    build_Heap ();
  }

  MinHeap::MinHeap (std::initializer_list<value_type> il)
    : m_data (il)
  {
    build_Heap ();
  }

  void
  MinHeap::pop (void)
  {
    m_data.front () = m_data.back ();
    m_data.pop_back ();
    sift_down (0);
  }

  void
  MinHeap::push (const value_type & element)
  {
    m_data.push_back (element);
    sift_up (m_data.size () - 1);
  }

  void
  MinHeap::replace (const value_type & element)
  {
    m_data.front () = element;
    sift_down (0);
  }
}
