// file: main.cc
#include <algorithm>
#include <iostream>
#include <iterator>
#include <mpi.h>
#include <vector>

#include "genetic.hh"
#include "multi_knapsack.hh"

using population_t =
  optimization::genetic<optimization::multi_knapsack>::population_type;

population_t
share_top_k (const population_t & local_top_k);


int
main (int argc, char * argv[])
{
  MPI_Init (&argc, &argv);
  int rank{0}, size{0};
  MPI_Comm_rank (MPI_COMM_WORLD, &rank);
  MPI_Comm_size (MPI_COMM_WORLD, &size);

  // Problem instance definition
  optimization::multi_knapsack global_instance (20, 17);
  global_instance.add_dimension (36., {11., 20., 5., 10., 20., 1., 20., 18., 9., 2., 3., 15., 16., 21., 23., 12., 11., 15., 11., 10.});
  global_instance.add_dimension (28., {11., 10., 1., 15., 10., 7., 12., 19., 8., 18., 3., 19., 12., 8., 15., 6., 3., 12., 8., 7.});
  global_instance.add_values ({30., 21., 15., 10., 7., 32., 39., 8., 38., 3., 39., 32., 28., 15., 20., 23., 32., 8., 27., 30.});

  // Create a GA solver
  auto local_metaheuristic =
    optimization::make_genetic (global_instance, 0.7, 0.05, 200 * rank * rank);

  constexpr std::size_t parallel_iterations = 10;
  constexpr std::size_t local_generations = 100;
  constexpr std::size_t population_size = 100;

  std::cout << "Initializing population\n";
  local_metaheuristic.initialize_population (population_size);
  local_metaheuristic.optimize (local_generations, std::cout);
  const std::size_t top_k = population_size / size;

  // Perform parallel iterations
  // ----------    YOUR CODE GOES HERE   ----------  

  for (std::size_t it = 0; it < parallel_iterations; ++it)
    {
      // share top k among all processes
      const population_t & new_global_population =
        share_top_k (local_metaheuristic.get_top_k (top_k));
      // set new population
      local_metaheuristic.set_population (new_global_population);
      // perform optimization again
      local_metaheuristic.optimize (local_generations, std::cout);
    }

  // share again top_k to get the best result
  const population_t & final_global_population =
    share_top_k (local_metaheuristic.get_top_k (top_k));
  local_metaheuristic.set_population (final_global_population);

  // print outputs
  if (rank == 0)
    {
      std::cout << "Final population:\n";
      for (auto const & individual : local_metaheuristic.get_population())
        {
          for (bool item : individual) std::cout << item;
          std::cout << "\n";
        }

      std::cout << "Top 10:\n";
      for (auto const & individual : local_metaheuristic.get_top_k (10))
        {
          for (bool item : individual) std::cout << item;
          std::cout << " fitness = "
                    << global_instance.individual_fitness (individual) << '\n';
        }
    }

  MPI_Finalize();
  return 0;
}


population_t
share_top_k (const population_t & local_top_k)
{
  int rank{0}, size{0};
  MPI_Comm_rank (MPI_COMM_WORLD, &rank);
  MPI_Comm_size (MPI_COMM_WORLD, &size);
  // initialize new_population with the local top_k elements
  population_t new_population = local_top_k;

  // for all processes
  for (int current_proc = 0; current_proc < size; ++current_proc)
    {
      // for every individual in local_top.
      // Note that here we exploit the fact that each process has the
      // same number of elements and that overall their number is equal to the
      // initial population size otherwise you should send
      // (or better compute) their number
      for (auto const & individual : local_top_k)
        {
          std::vector<unsigned short> item_unsigned_short;
          // convert bool vector into unsigned short vector
          std::copy (individual.cbegin (), individual.cend (),
                     std::back_inserter (item_unsigned_short));

          MPI_Bcast (item_unsigned_short.data(), item_unsigned_short.size(),
                     MPI_UNSIGNED_SHORT,
                     current_proc, MPI_COMM_WORLD);

          if (rank != current_proc)
            {
              // add item to new_population
              optimization::multi_knapsack::solution_type received;
              // convert unsigned short vector into bool vector
              std::copy (item_unsigned_short.cbegin (),
                         item_unsigned_short.cend (),
                         std::back_inserter (received));
              new_population.push_back (received);
            }
        }
    }

  return new_population;
}
