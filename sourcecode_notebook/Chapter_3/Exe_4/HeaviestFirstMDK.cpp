#include <iostream>
#include <utility>

#include "HeaviestFirstMDK.hpp"

// returns a vector of sorted indices with nonincreasing weight
std::vector<unsigned> HeaviestFirstMDK::sort (void) const
{
  std::vector<unsigned> sorted_idx;

  // first copy all indices
  for (unsigned i = 0; i < items.size (); ++i)
    sorted_idx.push_back (i);

  // sort indices
  for (std::size_t i = 0; i < items.size()-1; ++i)
    for (std::size_t j = i+1; j < items.size(); ++j)
      if (items[sorted_idx[i]].get_weight() < items[sorted_idx[j]].get_weight())
        {
          using std::swap;
          swap (sorted_idx[i], sorted_idx[j]);
        }

  return sorted_idx;
}
