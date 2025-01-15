/*#include <iostream>
#include "date_user.hpp"
#include "functions.hpp"*/

#include "Date.hpp" 

int main() 
    {
    int d, m, y;
    std::cout << "Insert day, month and year: " << std::endl;
    std::cin >> d >> m >> y;
    Date mydate(d, m, y);
    mydate.show_date();
  
    Date d1 = Date::next_Sunday(mydate);
    std::cout << "Next Sunday is: " << std::endl;
    d1.show_date();
    Date d2 = Date::next_Weekday(mydate);
    d2.show_date();
  
    return 0;  
    }
