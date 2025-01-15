#ifndef __DEQUE__
#define __DEQUE__

#include <vector>

namespace ds
{
  template <typename T>
  class Deque
  {
    typedef std::vector<std::vector<T> > container_type;

  public:
    typedef T value_type;
    typedef typename container_type::size_type size_type;

  private:
    container_type chunks;

    constexpr static size_type chunk_length = 8;
    constexpr static size_type initial_chunk_number = 3;

    size_type first_offset;
    size_type off_end_offset;

    inline bool
    on_boundary (size_type offset) const
    {
      return offset % chunk_length == 0;
    }

    void
    make_room_for (size_type);

  public:
    Deque (void)
      : first_offset (0), off_end_offset (0) {}

    inline size_type
    size (void) const
    {
      return off_end_offset - first_offset;
    }

    inline bool
    empty (void) const
    {
      return size () == 0;
    }

    value_type &
    operator [] (size_type);
    const value_type &
    operator [] (size_type) const;

    void
    push_front (const value_type &);
    void
    push_back (const value_type &);
  };

  template <typename T>
  void
  Deque<T>::make_room_for (size_type additions)
  {
    const size_type next_size = size () + additions;
    const size_type needed_chunks = next_size % chunk_length > 0
      ? next_size / chunk_length + 1
      : next_size / chunk_length;
    size_type next_chunks = chunks.size ();

    if (next_chunks == 0 and needed_chunks > 0)
      {
        next_chunks = initial_chunk_number;
      }

    if (first_offset == 0 or off_end_offset == chunks.size () * chunk_length)
      {
        next_chunks *= 2;
      }

    while (needed_chunks > next_chunks)
      {
        next_chunks *= 2;
      }

    if (next_chunks > chunks.size ())
      {
        const size_type center_before = chunks.size () / 2;
        chunks.resize (next_chunks);
        const size_type center_after = chunks.size () / 2;
        const size_type shift = center_after - center_before;

        for (size_type i = off_end_offset / chunk_length;
             i < next_chunks and i >= first_offset / chunk_length;
             --i)
          {
            using std::swap;
            swap (chunks[i], chunks[i + shift]);
          }

        if (empty ())
          {
            first_offset = off_end_offset =
              center_after * chunk_length + chunk_length / 2;  
            chunks[center_after].resize (chunk_length);
          }
        else
          {
            const size_type offset_shift = shift * chunk_length;
            first_offset += offset_shift;
            off_end_offset += offset_shift;
          }
      }
  }

  template <typename T>
  typename Deque<T>::value_type &
  Deque<T>::operator [] (size_type i)
  {
    const size_type real_idx = i + first_offset;
    const size_type chunk_idx (real_idx / chunk_length),
      position (real_idx % chunk_length);
    return chunks[chunk_idx][position];
  }

  template <typename T>
  const typename Deque<T>::value_type &
  Deque<T>::operator [] (size_type i) const
  {
    const size_type real_idx = i + first_offset;
    const size_type chunk_idx (real_idx / chunk_length),
      position (real_idx % chunk_length);
    return chunks[chunk_idx][position];
  }

  template <typename T>
  void
  Deque<T>::push_front (const value_type & element)
  {
    make_room_for (1);

    if (on_boundary (first_offset --))
      {
        const size_type new_chunk = first_offset / chunk_length;
        chunks[new_chunk].resize (chunk_length);
      }

    operator [] (0) = element;
  }

  template <typename T>
  void
  Deque<T>::push_back (const value_type & element)
  {
    make_room_for (1);

    if (on_boundary (off_end_offset ++))
      {
        const size_type new_chunk = off_end_offset / chunk_length;
        chunks[new_chunk].resize (chunk_length);
      }

    operator [] (size () - 1) = element;
  }
}

#endif
