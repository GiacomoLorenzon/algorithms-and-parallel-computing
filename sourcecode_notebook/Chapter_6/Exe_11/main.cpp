#include <iostream>

#include "deque.hpp"

int
main (void)
{
  ds::Deque d;

  int last = 0;
  std::cout << "Insert an integer" << std::endl;
  std::cin >> last;

  if (last < 0)
    {
      last *= -1;
    }

  for (int i = 0; i < last; ++i)
    {
      d.push_back (i);
      d.push_front (-i);
    }

  for (unsigned i = 0; i < d.size (); ++i)
    {
      std::cout << d[i] << "\n";
    }

  return 0;
}