#include <iostream>
#include <string>
#include <sstream>

#include "lil_sparse.hpp"

int
main (void)
{
  unsigned rows, columns;
  std::cin >> rows >> columns;

  using matrix = numeric::lil_sparse;
  matrix S (rows, columns);
  std::string line;
  while (std::getline (std::cin, line))
    {
      std::istringstream input (line);
      unsigned i, j;
      double a;
      if (input >> i >> j >> a) S.set (i, j, a);
    }

  for (matrix::size_type i = 0; i < S.rows (); ++i)
    {
      std::cout << S.get (i, 0);
      for (matrix::size_type j = 1; j < S.columns (); ++j)
        {
          std::cout << ' ' << S.get (i, j);
        }
      std::cout << std::endl;
    }

  return 0;
}
