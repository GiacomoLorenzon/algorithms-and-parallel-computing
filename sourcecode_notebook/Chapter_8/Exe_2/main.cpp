#include "HashMap.hpp"

#include <iostream>

int main (void)
{
   HashMap <int, int> t;
   for(int index = 0; index < 16; index++)
   {
      std::cerr << "Adding (" << index*8 << ", " << index*index*8 << ")" << std::endl;
      t.add(index*8, index * index * 8);
      t.dump_internal_structure();
   }
   return 0;
}
