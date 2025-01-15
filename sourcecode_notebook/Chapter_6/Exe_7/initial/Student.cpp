#include <iostream>

#include "Student.h"

namespace university
{
  Student::Student (unsigned id, const std::vector<unsigned> & grades)
    : id (id), grades (grades) {}

  Student::Student (unsigned id): id (id), grades () {}

  const std::vector<unsigned> & Student::getGrades() const
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
}
