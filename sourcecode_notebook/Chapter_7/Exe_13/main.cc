#include <iostream>
#include <mpi.h>
#include <vector>

#include "FunctionMinRn.hh"
#include "MPI_helpers.hh"

int
main (int argc, char *argv[])
{
  MPI_Init (&argc, &argv);

  constexpr double step = 1e-2;
  constexpr double tolerance = 1e-5;

  std::vector<Monomial> terms;
  terms.push_back (Monomial (2, {2, 0}));
  terms.push_back (Monomial (2, {1, 1}));
  terms.push_back (Monomial (2, {0, 2}));
  terms.push_back (Monomial (-2, {0, 1}));
  terms.push_back (Monomial (6, {0, 0}));

  FunctionRn f;
  for (const Monomial & m: terms)
    f.addMonomial (m);

  const Point P1 ({0, 0});
  const Point P2 ({2, 2});

  const unsigned rank = mpi::rank ();
  if (rank == 0)
    {
      std::cout << "Initial Points values" << std::endl;
      std::cout << f.eval (P1) << " " << f.eval (P2) << std::endl;
    }

  constexpr unsigned int max_iterations = 2e5;
  FunctionMinRn minRn (f, tolerance, step, max_iterations, {-5, -4}, {7, 9});

  const Point P = minRn.solve ();
  if (rank == 0)
    {
      std::cout << "Final solution standard grad: "
                << f.eval (P) << std::endl;
      P.print ();
    }

  const Point Q = minRn.solve_multistart (1000);
  if (rank == 0)
    {
      std::cout << "Final solution multi-start: "
                << f.eval (Q) << std::endl;
      Q.print ();
    }

  constexpr unsigned int n_domain_steps = 100;
  const Point R = minRn.solve_domain_decomposition (n_domain_steps, 100);
  if (rank == 0)
    {
      std::cout << "Final solution domain decomposition: "
                << f.eval (R) << std::endl;
      R.print ();
    }

  MPI_Finalize ();
  return 0;
}
