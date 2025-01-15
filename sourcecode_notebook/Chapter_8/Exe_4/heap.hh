#ifndef __HEAP__
#define __HEAP__

#include <functional>
#include <initializer_list>
#include <vector>

namespace ds
{
  template <typename T,
            typename Compare = std::less<T> >
  class Heap
  {
    typedef std::vector<T> container_type;

  public:
    typedef T value_type;
    typedef Compare value_compare;
    typedef typename container_type::size_type size_type;

  private:
    container_type m_data;
    value_compare m_compare;

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
    explicit Heap (const value_compare & comp = value_compare ())
      : m_compare (comp) {}

    template <typename InputIterator>
    Heap (InputIterator first, InputIterator last,
          const value_compare & comp = value_compare ());

    Heap (std::initializer_list<value_type> il,
          const value_compare & comp = value_compare ());

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

  template <typename T, typename Compare>
  void
  Heap<T, Compare>::sift_down (size_type i)
  {
    bool keep_sifting = true;

    while (keep_sifting and i < m_data.size ())
      {
        keep_sifting = false;

        const size_type l = left (i), r = right (i);
        size_type best = i;

        if (l < m_data.size () and m_compare (m_data[l], m_data[best]))
          {
            best = l;
            keep_sifting = true;
          }

        if (r < m_data.size () and m_compare (m_data[r], m_data[best]))
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

  template <typename T, typename Compare>
  void
  Heap<T, Compare>::sift_up (size_type i)
  {
    while (i > 0 and m_compare (m_data[i], m_data[parent (i)]))
      {
        using std::swap;
        swap (m_data[i], m_data[parent (i)]);
        i = parent (i);
      }
  }

  template <typename T, typename Compare>
  void
  Heap<T, Compare>::build_Heap (void)
  {
    for (size_type i = parent (m_data.size ());
         i >= 0 and i < m_data.size (); --i)
      {
        sift_down (i);
      }
  }

  template <typename T, typename Compare>
  template <typename InputIterator>
  Heap<T, Compare>::Heap (InputIterator first, InputIterator last,
                          const value_compare & comp)
    : m_data (first, last), m_compare (comp)
  {
    build_Heap ();
  }

  template <typename T, typename Compare>
  Heap<T, Compare>::Heap (std::initializer_list<value_type> il,
                          const value_compare & comp)
    : m_data (il), m_compare (comp)
  {
    build_Heap ();
  }

  template <typename T, typename Compare>
  void
  Heap<T, Compare>::pop (void)
  {
    m_data.front () = m_data.back ();
    m_data.pop_back ();
    sift_down (0);
  }

  template <typename T, typename Compare>
  void
  Heap<T, Compare>::push (const value_type & element)
  {
    m_data.push_back (element);
    sift_up (m_data.size () - 1);
  }

  template <typename T, typename Compare>
  void
  Heap<T, Compare>::replace (const value_type & element)
  {
    m_data.front () = element;
    sift_down (0);
  }
}

#endif
