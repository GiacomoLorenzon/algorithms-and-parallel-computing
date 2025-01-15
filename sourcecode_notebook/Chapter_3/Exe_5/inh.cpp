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
  student (const string & name, const string & surname, size_t id)
    : name (name), surname (surname), id (id) {}
};

class freshman: public student
{
  std::vector<course & > classes;

  std::vector<double> show_grades (student & s)
  {
    return s.grades;
  }
};
