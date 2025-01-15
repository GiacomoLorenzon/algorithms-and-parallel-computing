#include <iostream>

#include "search.h"
#include "timing.h"

namespace university
{
   bool binary_search (const std::vector<university::Student> & stud_vec, unsigned stud_id)
   {
      timing::time_point start = std::chrono::system_clock::now();

      std::vector<university::Student>::const_iterator begin = stud_vec.cbegin(), 
         end = stud_vec.cend(),
         // original midpoint
         mid = begin + (end - begin) / 2;
      unsigned n_iter = 1;

      while (begin != end and mid->getId() != stud_id)
      {
         /* end is meant to be invalid, so in both cases
          * we are ignoring mid at the following iteration
          */
         if (stud_id < mid->getId())
            end = mid;
         else
            begin = mid + 1;

         mid = begin + (end - begin) / 2;
         ++n_iter;
      }

      std::cout << "Number of Iterations " << n_iter << "\n";

      timing::time_point finish = std::chrono::system_clock::now();
      timing::elapsed_between (start, finish);

      if (mid != stud_vec.cend() and stud_id == mid->getId())
      {
         return true;
      }
      else
      {
         return false;
      }
   }

   bool set_search (const std::set<university::Student> & stud_set, unsigned stud_id)
   {
      timing::time_point start = std::chrono::system_clock::now();
      const university::Student s(stud_id);
      const std::set<university::Student>::const_iterator it = stud_set.find (s);

      timing::time_point finish = std::chrono::system_clock::now();
      timing::elapsed_between (start, finish);

      return it != stud_set.cend();
   }

   bool map_search (const std::unordered_map<unsigned, university::Student> & stud_map, unsigned stud_id)
   {
      timing::time_point start = std::chrono::system_clock::now();
      const std::unordered_map<unsigned, university::Student>::const_iterator it =
         stud_map.find (stud_id);

      timing::time_point finish = std::chrono::system_clock::now();
      timing::elapsed_between (start, finish);

      return it != stud_map.cend();
   }
}
