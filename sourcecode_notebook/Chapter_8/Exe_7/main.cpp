#include <functional>
#include <iostream>
#include <random>

#include "generation.hpp"
#include "sorting.hpp"

int main (void)
{
  constexpr unsigned bound = 8;
  std::mt19937 generator;
  
  std::uniform_int_distribution<unsigned> distribution (0, bound); 
  
  auto pseudo_random = std::bind (distribution, generator); 
  
  constexpr unsigned count = 10;
  std::vector<unsigned> numbers;
  
  generation::create_numbers (pseudo_random, count, 
                                    std::back_inserter (numbers));

  const std::vector<unsigned> sorted = 
                      sorting::counting_sort (numbers, bound + 1);
  
  for (unsigned value : sorted)
    {
      std::cout << value << std::endl;
    }
    
  return 0;
}
