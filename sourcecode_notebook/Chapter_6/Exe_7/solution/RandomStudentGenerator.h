#ifndef RANDOMSTUDENTGENERATOR_H_
#define RANDOMSTUDENTGENERATOR_H_

#include <random>

namespace university
{
  class Student;

  class RandomStudentGenerator
  {
    unsigned next_id;

    std::mt19937 generator;
    std::uniform_int_distribution<unsigned> grade_distribution;
    std::uniform_int_distribution<unsigned> number_distribution;

  public:
    RandomStudentGenerator (void);
    RandomStudentGenerator (unsigned first_id, unsigned lowest_grade,
                            unsigned highest_grade, unsigned n_grades,
                            unsigned seed = 0u);

    Student nextStudent (void);
  };
}

#endif /* RANDOMSTUDENTGENERATOR_H_ */
