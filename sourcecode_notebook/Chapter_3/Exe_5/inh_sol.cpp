#include <vector>
#include <string>

using namespace std;

class course
{
  // ...
};

class department
{
  // ...
};

class student
{
  
protected:
  string name;
  string surname;
  size_t id;
  department & dpt;
  std::vector<double> grades;

public:
  student (const string & name, const string & surname, size_t id, department & d)
    : name (name), surname (surname), id (id), dpt (d) {}

  const std::vector<double> & get_grades (void) const
  {
    return grades;
  }
};

class freshman: public student
{
  std::vector<course * > classes;

  std::vector<double> show_grades (const student & s)
  {
    return s.get_grades();
  }
};
