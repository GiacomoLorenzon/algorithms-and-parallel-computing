#ifndef HEAVIESTFIRSTMDK_H_
#define HEAVIESTFIRSTMDK_H_

#include "MultiDimKnapsack.hpp"

class HeaviestFirstMDK: public MultiDimKnapsack
{
  // returns a vector of sorted item indices
  virtual std::vector<unsigned> sort (void) const override;

public:
  HeaviestFirstMDK (int n_items, double max_weight, double max_size)
    : MultiDimKnapsack (n_items,  max_weight,  max_size) {}
};


#endif /* HEAVIESTFIRSTMDK_H_ */
