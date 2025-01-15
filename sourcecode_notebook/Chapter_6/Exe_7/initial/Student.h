#ifndef STUDENT_H_
#define STUDENT_H_

#include <vector>

namespace university
{
  class Student
  {
    unsigned id;
    std::vector<unsigned> grades;

  public:
    Student (unsigned, const std::vector<unsigned> &);
    explicit Student (unsigned);

    const std::vector<unsigned> & getGrades (void) const;
    unsigned getId (void) const;

    void setGrades (const std::vector<unsigned> &);
    void setId (unsigned);

    void print (void) const;
  };
}

#endif /* STUDENT_H_ */
