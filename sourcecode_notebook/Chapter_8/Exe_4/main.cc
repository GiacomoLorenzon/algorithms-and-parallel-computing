#include <functional>
#include <iostream>
#include <vector>

#include "heap.hh"

int
main (void)
{
  std::cout << "Min Heap\n";
  ds::Heap<int> min_Heap {17, 18, 5, 7};
  std::cout << min_Heap.peek () << "\n";

  min_Heap.replace (22);
  std::cout << min_Heap.peek () << "\n";

  min_Heap.pop ();
  std::cout << min_Heap.peek () << "\n";

  min_Heap.push (2);
  std::cout << min_Heap.peek () << "\n";

  min_Heap.push (45);
  std::cout << min_Heap.peek () << "\n\n";

  std::cout << "all values:\n";

  while (not min_Heap.empty ())
    {
      std::cout << min_Heap.peek () << " ";
      min_Heap.pop ();
    }

  std::cout << "\n\nMax Heap\n";
  std::vector<int> aux {17, 18, 5, 7};
  ds::Heap<int, std::greater<int>> max_Heap (aux.cbegin (),
                                             aux.cend ());
  std::cout << max_Heap.peek () << "\n";

  max_Heap.replace (22);
  std::cout << max_Heap.peek () << "\n";

  max_Heap.pop ();
  std::cout << max_Heap.peek () << "\n";

  max_Heap.push (2);
  std::cout << max_Heap.peek () << "\n";

  max_Heap.push (45);
  std::cout << max_Heap.peek () << "\n\n";

  std::cout << "all values:\n";

  while (not max_Heap.empty ())
    {
      std::cout << max_Heap.peek () << " ";
      max_Heap.pop ();
    }

  std::cout << "\n\nBlackboard example:\n";

  ds::Heap<long> big_min_Heap {-1l, 17l, 289l, 35l,
      82l, 2006l, -27l, 0l, 73l, -42l};

  while (not big_min_Heap.empty ())
    {
      std::cout << big_min_Heap.peek () << " ";
      big_min_Heap.pop ();
    }

  std::cout << "\n";

  return 0;
}
