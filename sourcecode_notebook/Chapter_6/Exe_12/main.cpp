#include <iostream>
#include <vector>

#include "minHeap.hpp"

int
main (void)
{
  std::cout << "Min Heap\n";
  ds::MinHeap min_Heap {17, 18, 5, 7};
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

  return 0;
}
