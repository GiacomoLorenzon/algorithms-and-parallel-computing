#ifndef __DEQUE__
#define __DEQUE__

#include <vector>

namespace ds
{
  class Deque
  {
    typedef std::vector<std::vector<int> > container_type;

  public:
    typedef int value_type;
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

}

#endif
