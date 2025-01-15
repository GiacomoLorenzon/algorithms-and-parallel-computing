#ifndef _H_DATE_H_
#define _H_DATE_H_

#include <iostream>
#include <string>

class Date {

private:

    int day, month, year;
    bool leap;
    
    int get_max (void) const; 
    int dooms_month (void) const;
    int Doomsday (void) const;
    
    static std::string day_name (int d);

public:

    Date (int d, int m, int y);
    
    void add_days (int n); 
    
    int get_day (void) const {return day;}
    int get_month (void) const {return month;}
    int get_year (void) const {return year;}
    
    void show_date (void) const;
    
    static bool leap_year (int y);
    static Date next_Sunday (const Date &d);
    static Date next_Weekday (const Date &d);

};

#endif /* _H_DATE_H_ */
