#include <iostream>

#include "genetic.hh"
#include "multi_knapsack.hh"

int
main (void)
{
  optimization::multi_knapsack instance (20, 17);
  instance.add_dimension (36., {11., 20., 5., 10., 20., 1., 20., 18., 9., 2., 3., 15., 16., 21., 23., 12., 11., 15., 11., 10.});
  instance.add_dimension (28., {11., 10., 1., 15., 10., 7., 12., 19., 8., 18., 3., 19., 12., 8., 15., 6., 3., 12., 8., 7.});
  instance.add_values ({30., 21., 15., 10., 7., 32., 39., 8., 38., 3., 39., 32., 28., 15., 20., 23., 32., 8., 27., 30.});

  auto metaheuristic = optimization::make_genetic (instance, 0.7, 0.05, 289);
  std::cout << "Initializing population\n";
  metaheuristic.initialize_population (100);
  metaheuristic.optimize (60, std::cout);

  std::cout << "Final population:\n";
  for (auto const& individual : metaheuristic.get_population ())
    {
      for (bool item : individual) std::cout << item;
      std::cout << "\n";
    }

  std::cout << "Top 10:\n";
  for (auto const& individual : metaheuristic.get_top_k (10))
    {
      for (bool item : individual) std::cout << item;
      std::cout << " fitness = " << instance.individual_fitness (individual) << '\n';
    }
  return 0;
}
