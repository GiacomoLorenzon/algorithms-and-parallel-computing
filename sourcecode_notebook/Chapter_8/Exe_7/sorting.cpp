#include "sorting.hpp"

namespace sorting {

  std::vector<unsigned>
  counting_sort (const std::vector<unsigned> & data, unsigned bound)
  {
    std::vector<unsigned> counts (bound, 0);
    for (auto it = data.cbegin (); it != data.cend (); ++it)
      {
        ++counts[*it];
      }
    for (unsigned i = 1; i < bound; ++i)
      {
        counts[i] += counts[i - 1];
      }
    std::vector<unsigned> result (data.size ());
    for (auto it = data.crbegin (); it != data.crend (); ++it)
      {
        result[--counts[*it]] = *it;
      }
    return result;
  }

}
