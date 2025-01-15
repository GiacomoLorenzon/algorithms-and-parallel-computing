#include <iostream>

#include "Item.hpp"
#include "MultiDimKnapsack.hpp"
#include "LargestFirstMDK.hpp"
#include "HeaviestFirstMDK.hpp"

using namespace std;

int main()
{
  LargestFirstMDK mkp(10, 100, 20);
  //HeaviestFirstMDK mkp (10, 11, 200);
  mkp.print();

  vector<unsigned> solution = mkp.solve();

  std::cout << "Final solution" << std::endl;
  for (unsigned index: solution)
    std::cout << index << std::endl;

  return 0;
}
