#include <algorithm>
#include <chrono>
#include <iostream>
#include <string>
#include <set>
#include <unordered_map>
#include <vector>

#include "RandomStudentGenerator.h"
#include "search.h"
#include "Student.h"
#include "timing.h"

typedef std::vector<university::Student> stud_vec_type;
typedef std::set<university::Student> stud_set_type;
typedef std::unordered_map<unsigned, university::Student> stud_map_type;

int main (void)
{
  constexpr unsigned n_students = 1000;
  stud_vec_type stud_vec;
  stud_set_type stud_set;
  stud_map_type stud_map;

  university::RandomStudentGenerator rs;

  for (unsigned i = 0; i < n_students; ++i)
    {
      university::Student random_stud = rs.nextStudent();
      stud_vec.push_back (random_stud);
      stud_set.insert (random_stud);
      stud_map.insert (std::make_pair (random_stud.getId(), random_stud));
    }

  const unsigned stud_ok_id = stud_vec[stud_vec.size() / 2].getId();
  const unsigned stud_ko_id = stud_vec.back().getId() + 1;

  std::cout << "*********initial binary search on vector*********\n";
  std::cout << (university::binary_search (stud_vec, stud_ko_id) ? "Found!\n" : "Not found\n");
  std::cout << (university::binary_search (stud_vec, stud_ko_id) ? "Found!\n" : "Not found\n");


  std::cout << "******************set search******************\n";
  std::cout << (university::set_search (stud_set, stud_ko_id) ? "Found!\n" : "Not found\n");
  std::cout << (university::set_search (stud_set, stud_ok_id) ? "Found!\n" : "Not found\n");

  std::cout << "*************map search*************\n";
  std::cout << (university::map_search (stud_map, stud_ko_id) ? "Found!\n" : "Not found\n");
  std::cout << (university::map_search (stud_map, stud_ok_id) ? "Found!\n" : "Not found\n");

  timing::time_point start, finish;
  std::cout << "*************STL::binary_search*************\n";
  university::Student s1(stud_ko_id);
  start = std::chrono::system_clock::now();
  std::cout << (std::binary_search (stud_vec.cbegin (), stud_vec.cend(), s1) ? "Found!\n" : "Not found\n");
  finish = std::chrono::system_clock::now();
  timing::elapsed_between (start, finish);

  university::Student s2(stud_ok_id);
  start = std::chrono::system_clock::now();
  std::cout << (std::binary_search (stud_vec.cbegin (), stud_vec.cend(), s2)  ? "Found!\n" : "Not found\n");
  finish = std::chrono::system_clock::now();
  timing::elapsed_between (start, finish);

  return 0;
}
