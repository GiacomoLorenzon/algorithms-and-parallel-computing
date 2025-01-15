#include <iostream>
#include <utility>

#include "LargestFirstMDK.hpp"

// returns a vector of sorted item indices with nonincreasing size
std::vector<unsigned> LargestFirstMDK::sort (void) const
{
  std::vector<unsigned> sorted_idx;

  // first copy all indices
  for (unsigned i = 0; i < items.size (); ++i)
    sorted_idx.push_back (i);

  // sort indices
  for (std::size_t i = 0; i < items.size()-1; ++i)
    for (std::size_t j = i+1; j < items.size(); ++j)
      if (items[sorted_idx[i]].get_size() < items[sorted_idx[j]].get_size())
        {
          using std::swap;
          swap (sorted_idx[i], sorted_idx[j]);
        }

  return sorted_idx;
}
