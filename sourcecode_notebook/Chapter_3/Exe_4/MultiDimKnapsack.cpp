#include <iostream>

#include "MultiDimKnapsack.hpp"

// generate n_items random items and set knapsack capacities
MultiDimKnapsack::MultiDimKnapsack (int n_items, double max_weight,
                                    double max_size)
  : w(max_weight), s(max_size)
{
  for (std::size_t i = 0; i < n_items; ++i)
    {
      const double weight = i + 1.;
      const double size = n_items - i;
      const double value = (i + 1) * 100.;
      items.push_back (Item (weight, size, value));
    }
}

// returns the set of items included in the solution
std::vector<unsigned> MultiDimKnapsack::solve (void) const
{
  std::vector<unsigned> solution;
  double current_weight = 0;
  double current_size = 0;

  // compute solution
  std::vector<unsigned> sorted_idx = sort();
  for (unsigned idx: sorted_idx)
    {
      // check if adding the current item would lead to capacity saturation
      const bool has_room = (current_size + items[idx].get_size () <= s)
        and (current_weight + items[idx].get_weight () <= w);

      // if there is still room add the item
      if (has_room)
        {
          solution.push_back(idx);
          current_weight += items[idx].get_weight();
          current_size += items[idx].get_size();
        }
    }

  return solution;
}

void MultiDimKnapsack::print (void) const
{
  for (const Item & item: items)
    {
      item.print();
      std::cout << std::endl;
    }
}
