#include <vector>

#include "RandomStudentGenerator.h"
#include "Student.h"

namespace university
{
  RandomStudentGenerator::RandomStudentGenerator (void)
    : RandomStudentGenerator (1, 18, 30, 20) {}

  RandomStudentGenerator::RandomStudentGenerator (unsigned first_id,
                                                  unsigned lowest_grade,
                                                  unsigned highest_grade,
                                                  unsigned n_grades,
                                                  unsigned seed)
    : next_id (first_id), generator (seed),
      grade_distribution (lowest_grade, highest_grade),
      number_distribution (1, n_grades) {}

  Student RandomStudentGenerator::nextStudent (void)
  {
    const unsigned n_grades = number_distribution (generator);
    std::vector<unsigned> grades (n_grades);

    for (unsigned & grade : grades)
      grade = grade_distribution (generator);

    return Student (next_id++, grades);
  }
}
