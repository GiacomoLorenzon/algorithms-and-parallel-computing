#ifndef DATE_HH_
#define DATE_HH_

///STD include
#include <string>

class Date
{
private:
  int day = 1, month = 1, year = 1972;
  
public:  
  Date (void) = default;
  Date (const Date&) = default;

  //format (year-month-day) needs to be checked
  Date (const std::string& str);

  const std::string Print (void) const;

  // comparing two dates
  friend bool operator< (const Date&, const Date&);
};

bool operator< (const Date&, const Date&);

#endif
