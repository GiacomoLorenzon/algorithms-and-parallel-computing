#ifndef SEARCH_HH
#define SEARCH_HH

#include <set>
#include <unordered_map>
#include <vector>

#include "Student.h"

namespace university
{

   bool binary_search (const std::vector<university::Student> & stud_vec, unsigned stud_id);

   bool set_search (const std::set<university::Student> & stud_set, unsigned stud_id);

   bool map_search (const std::unordered_map<unsigned, university::Student> & stud_map, unsigned stud_id);
}

#endif // SEARCH_HH
