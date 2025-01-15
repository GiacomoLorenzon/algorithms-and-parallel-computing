#ifndef GENETIC_HH
#define GENETIC_HH

#include <algorithm>
#include <cmath>
#include <functional>
#include <ostream>
#include <random>
#include <utility>
#include <vector>

namespace optimization
{
  template <typename Problem>
  class genetic
  {
  public:
    using problem_type = Problem;
    using population_type = std::vector<typename problem_type::solution_type>;
    using fitness_type = std::vector<double>;

  private:
    problem_type m_problem;
    const double m_crossover_fraction;
    const double m_mutation_probability;
    std::mt19937_64 m_random_engine;
    population_type m_population;
    fitness_type m_fitness;

  public:
    genetic (problem_type const&, double crossover,
             double mutation, std::size_t seed = 0);

  private:
    void
    evaluate_fitness (void);
    population_type
    select (std::size_t);
    population_type
    recombine (void);
    void
    mutate (void);
    void
    enforce_feasibility (void);
    void
    evolve_generation (void);

  public:
    void
    initialize_population (std::size_t population_size);
    void
    optimize (std::size_t generations, std::ostream &);

    population_type
    get_top_k (std::size_t k);

    population_type const&
    get_population (void) const;
    void
    set_population (population_type const&);
  };

  template <typename Problem>
  genetic<Problem>
  make_genetic (Problem const& problem, double crossover, double mutation,
                std::size_t seed = 0)
  {
    genetic<Problem> ga (problem, crossover, mutation, seed);
    return ga;
  }

  template <typename Problem>
  genetic<Problem>::genetic (problem_type const& problem, double crossover,
                             double mutation, std::size_t seed)
    : m_problem (problem), m_crossover_fraction (crossover),
      m_mutation_probability (mutation), m_random_engine (seed) {}

  template <typename Problem>
  void
  genetic<Problem>::initialize_population (std::size_t population_size)
  {
    m_population.clear ();
    std::generate_n (std::back_inserter (m_population), population_size,
                     std::bind (&problem_type::random_individual, &m_problem));
  }

  template <typename Problem>
  void
  genetic<Problem>::evaluate_fitness (void)
  {
    using namespace std::placeholders;
    fitness_type population_fitness;
    std::transform (m_population.cbegin (), m_population.cend (),
                    std::back_inserter (population_fitness),
                    std::bind (&problem_type::individual_fitness,
                               &m_problem, _1));
    using std::swap;
    swap (population_fitness, m_fitness);
  }

  template <typename Problem>
  typename genetic<Problem>::population_type
  genetic<Problem>::select (std::size_t count)
  {
    std::discrete_distribution<typename population_type::size_type>
      sampler (m_fitness.cbegin (), m_fitness.cend ());
    population_type selected;
    std::generate_n (std::back_inserter (selected), count,
                     [&] (void)
                     {
                       const typename population_type::size_type index =
                         sampler (m_random_engine);
                       return m_population[index];
                     });
    return selected;
  }

  template <typename Problem>
  typename genetic<Problem>::population_type
  genetic<Problem>::recombine (void)
  {
    const std::size_t parent_count =
      std::round (m_crossover_fraction * m_population.size () / 2);
    population_type parent1 = select (parent_count),
      parent2 = select (parent_count), recombined;
    typename population_type::iterator it1 = parent1.begin (),
      it2 = parent2.begin ();
    while (it1 != parent1.end ())
      {
        std::pair<typename problem_type::solution_type,
                  typename problem_type::solution_type>
          pair = m_problem.cross_over (*it1++, *it2++);
        recombined.push_back (pair.first);
        recombined.push_back (pair.second);
      }
    return recombined;
  }

  template <typename Problem>
  void
  genetic<Problem>::mutate (void)
  {
    std::bernoulli_distribution bernoulli (m_mutation_probability);
    for (typename problem_type::solution_type & individual : m_population)
      if (bernoulli (m_random_engine))
        m_problem.mutate (individual);
  }

  template <typename Problem>
  void
  genetic<Problem>::enforce_feasibility (void)
  {
    for (typename problem_type::solution_type & individual : m_population)
      m_problem.make_feasible (individual);
  }

  template <typename Problem>
  void
  genetic<Problem>::evolve_generation (void)
  {
    evaluate_fitness ();
    const std::size_t selected_count =
      std::round ((1 - m_crossover_fraction) * m_population.size ());
    population_type next_generation = select (selected_count),
      crossed_over = recombine ();
    next_generation.insert (next_generation.end (),
                            crossed_over.cbegin (), crossed_over.cend ());
    using std::swap;
    swap (next_generation, m_population);
    mutate ();
    enforce_feasibility ();
  }

  template <typename Problem>
  void
  genetic<Problem>::optimize (std::size_t generations, std::ostream & out)
  {
    for (std::size_t generation = 1; generation <= generations; ++generation)
      {
        out << "Evolving generation " << generation << ": ";
        evolve_generation ();
        out << "population size = " << m_population.size () << ", ";
        const typename problem_type::solution_type best =
          get_top_k (1).front ();
        const double fitness = m_problem.individual_fitness (best);
        out << "best fitness = " << fitness << '\n';
      }
  }

  template <typename Problem>
  typename genetic<Problem>::population_type
  genetic<Problem>::get_top_k (std::size_t k)
  {
    evaluate_fitness ();
    std::vector<typename population_type::size_type> indices;
    for (typename population_type::size_type i = 0;
         i < m_population.size (); ++i)
      {
        indices.push_back (i);
      }
    std::nth_element (indices.begin (), indices.begin () + k, indices.end (),
                      [&] (typename population_type::size_type i,
                           typename population_type::size_type j)
                      {
                        return m_fitness[i] > m_fitness[j];
                      });
    indices.resize (k);
    population_type top_k;
    for (typename population_type::size_type i : indices)
      top_k.push_back (m_population[i]);
    return top_k;
  }

  template <typename Problem>
  typename genetic<Problem>::population_type const&
  genetic<Problem>::get_population (void) const
  {
    return m_population;
  }

  template <typename Problem>
  void
  genetic<Problem>::set_population (population_type const& population)
  {
    m_population = population;
  }
}

#endif // GENETIC_HH
