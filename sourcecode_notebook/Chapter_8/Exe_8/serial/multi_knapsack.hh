#ifndef MULTI_KNAPSACK_HH
#define MULTI_KNAPSACK_HH

#include <random>
#include <utility>
#include <vector>

namespace optimization
{
  class multi_knapsack
  {
  public:
    using solution_type = std::vector<bool>;

  private:
    const std::size_t m_items;
    std::vector<double> m_values;
    std::vector< std::vector<double> > m_weights;
    std::vector<double> m_capacities;
    std::mt19937_64 m_random_engine;

    bool
    check_feasibility (solution_type const&) const;

  public:
    explicit multi_knapsack (std::size_t items, std::size_t seed = 0);

    void
    add_dimension (double capacity, std::vector<double> const& weights);
    void
    add_values (std::vector<double> const&);

    solution_type
    random_individual (void);
    double
    individual_fitness (solution_type const&) const;
    std::pair<solution_type, solution_type>
    cross_over (solution_type const&, solution_type const&);
    void
    mutate (solution_type &);
    void
    make_feasible (solution_type &);
  };
}

#endif // MULTI_KNAPSACK_HH
