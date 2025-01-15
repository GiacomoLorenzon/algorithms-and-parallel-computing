#include "deque.hpp"

namespace ds
{
  void
  Deque::make_room_for (size_type additions)
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

  Deque::value_type &
  Deque::operator [] (size_type i)
  {
    const size_type real_idx = i + first_offset;
    const size_type chunk_idx (real_idx / chunk_length),
      position (real_idx % chunk_length);
    return chunks[chunk_idx][position];
  }

  const Deque::value_type &
  Deque::operator [] (size_type i) const
  {
    const size_type real_idx = i + first_offset;
    const size_type chunk_idx (real_idx / chunk_length),
      position (real_idx % chunk_length);
    return chunks[chunk_idx][position];
  }

  void
  Deque::push_front (const value_type & element)
  {
    make_room_for (1);

    if (on_boundary (first_offset --))
      {
        const size_type new_chunk = first_offset / chunk_length;
        chunks[new_chunk].resize (chunk_length);
      }

    operator [] (0) = element;
  }

  void
  Deque::push_back (const value_type & element)
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
