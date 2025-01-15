#include <iostream>

#include "deque.hh"

int
main (void)
{
  ds::Deque<int> d;

  int last = 0;
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