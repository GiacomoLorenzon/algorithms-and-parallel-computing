#include <algorithm>

#include "multi_knapsack.hh"

namespace optimization
{
  multi_knapsack::multi_knapsack (std::size_t items, std::size_t seed)
    : m_items (items), m_random_engine (seed) {}

  void
  multi_knapsack::add_dimension (double capacity,
                                 std::vector<double> const& weights)
  {
    m_capacities.push_back (capacity);
    m_weights.push_back (weights);
  }

  void
  multi_knapsack::add_values (std::vector<double> const& values)
  {
    m_values = values;
  }

  bool
  multi_knapsack::check_feasibility (solution_type const& individual) const
  {
    bool feasible = true;
    std::vector< std::vector<double> >::const_iterator w_it =
      m_weights.cbegin ();
    std::vector<double>::const_iterator c_it = m_capacities.cbegin ();
    while (feasible and c_it != m_capacities.cend ())
      {
        std::vector<double> const& current_weights = *w_it++;
        double total = 0.0;
        for (std::size_t i = 0; i < m_items; ++i)
          if (individual[i])
            total += current_weights[i];
        feasible = (total <= *c_it++);
      }
    return feasible;
  }

  multi_knapsack::solution_type
  multi_knapsack::random_individual (void)
  {
    std::bernoulli_distribution bernoulli (0.5);
    solution_type individual;
    for (std::size_t i = 0; i < m_items; ++i)
      individual.push_back (bernoulli (m_random_engine));
    return individual;
  }

  double
  multi_knapsack::individual_fitness (solution_type const& individual) const
  {
    double fitness = 0.0;
    if (check_feasibility (individual))
      {
        for (std::size_t i = 0; i < m_items; ++i)
          if (individual[i])
            fitness += m_values[i];
      }
    return fitness;
  }

  std::pair<multi_knapsack::solution_type, multi_knapsack::solution_type>
  multi_knapsack::cross_over (solution_type const& one,
                              solution_type const& two)
  {
    std::uniform_int_distribution<solution_type::size_type>
      sampler (0, m_items - 1);
    const solution_type::size_type index = sampler (m_random_engine);
    std::pair<multi_knapsack::solution_type, multi_knapsack::solution_type>
      offspring {one, two};
    std::swap_ranges (offspring.first.begin () + index, offspring.first.end (),
                      offspring.second.begin () + index);
    return offspring;
  }

  void
  multi_knapsack::mutate (solution_type & individual)
  {
    std::uniform_int_distribution<solution_type::size_type>
      sampler (0, m_items - 1);
    const solution_type::size_type index = sampler (m_random_engine);
    individual[index] = not individual[index];
  }

  void
  multi_knapsack::make_feasible (solution_type & individual)
  {
    if (not check_feasibility (individual))
      {
        individual.assign (m_items, false);
        std::uniform_int_distribution<solution_type::size_type>
          sampler (0, m_items - 1);
        const solution_type::size_type index = sampler (m_random_engine);
        individual[index] = true;
      }
  }
}
