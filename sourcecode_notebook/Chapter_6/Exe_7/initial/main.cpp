#include <iostream>
#include <string>
#include <vector>

#include "RandomStudentGenerator.h"
#include "search.h"
#include "Student.h"
#include "timing.h"

typedef std::vector<university::Student> stud_vec_type;

int main (void)
{
  constexpr unsigned n_students = 1000;
  stud_vec_type stud_vec;

  university::RandomStudentGenerator rs;

  // create the vector with students sorted by id
  for (unsigned i = 0; i < n_students; ++i)
    {
      university::Student random_stud = rs.nextStudent();
      stud_vec.push_back (random_stud);
    }

  const unsigned stud_ok_id = stud_vec[stud_vec.size() / 2].getId();
  const unsigned stud_ko_id = stud_vec.back().getId() + 1;

  std::cout << "*********initial binary search on vector*********\n";
  std::cout << (university::binary_search (stud_vec, stud_ko_id) ? "Found!\n" : "Not found\n");
  std::cout << (university::binary_search (stud_vec, stud_ko_id) ? "Found!\n" : "Not found\n");

  return 0;
}
