#include <iostream>

#include "Student.h"

namespace university
{
  Student::Student (unsigned _id, const std::vector<unsigned> & _grades)
    : id (_id), grades (_grades) {}

  Student::Student (unsigned _id): id (_id), grades () {}

  const std::vector<unsigned> & Student::getGrades (void) const
  {
    return grades;
  }

  unsigned Student::getId (void) const
  {
    return id;
  }

  void Student::setGrades (const std::vector<unsigned> & new_grades)
  {
    grades = new_grades;
  }

  void Student::setId (unsigned new_id)
  {
    id = new_id;
  }

  void Student::print (void) const
  {
    std::cout << id << ":\n";

    for (unsigned grade : grades)
      std::cout << grade << " ";

    std::cout << std::endl;
  }

  bool operator < (const Student & lhs, const Student & rhs)
  {
    return lhs.getId() < rhs.getId();
  }
}
