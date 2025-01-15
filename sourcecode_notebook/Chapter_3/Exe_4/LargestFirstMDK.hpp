#ifndef LARGESTFIRSTMDK_H_
#define LARGESTFIRSTMDK_H_

#include "MultiDimKnapsack.hpp"

class LargestFirstMDK: public MultiDimKnapsack
{
  // returns a vector of sorted item indices
  virtual std::vector<unsigned> sort (void) const override;

public:
  LargestFirstMDK (int n_items, double max_weight, double max_size)
    : MultiDimKnapsack (n_items,  max_weight,  max_size) {}
};

#endif /* LARGESTFIRSTMDK_H_ */
