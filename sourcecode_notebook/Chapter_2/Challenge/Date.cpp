#include "Date.hpp"
              
// constructor
    
Date::Date (int d, int m, int y)
    {
    leap = leap_year(y);
    year = y;
    if (m>12 || m<1) 
        {
        std::cerr << "Month value m = "<< m <<" invalid. Value set to default m = 1." 
              << std::endl;
        month=1;
        }
    else
        month=m;

    int maxd = get_max();

    if (d<1 || d>maxd)
        {
        std::cerr << "Day value d = "<< d <<" invalid. Value set to default d = 1." 
              << std::endl;
        day=1;
        }
    else
        day=d;
    }
    
// public methods    
    
void
Date::add_days(int n)
    {
    int max;
    while (n > 0)
        {
        max = get_max();
        if ( max-day >= n)
            {
            day += n;
            n = 0;
            }
        else
            {
            n -= (max-day);
            day = 0;

            if (month==12)
                {
                month = 1;
                year++;
                }
            else month++;
            }
        }

    while (n<0)
        {
        if (day > -n)
            {
            day += n;
            n = 0;
            }
        else
            {
            if (month==1)
                {
                month = 12;
                year--;
                }
            else
                month--;
            max = get_max();
            n += (day-1);
            day = max+1;
            }
        }
    }    
    
void
Date::show_date (void) const
    {
    std::cout << "Date: "<<day <<"/"<<month <<"/"<<year << '\n'<< std::endl;
    }  
    
bool
Date::leap_year (int y)
    {
    bool l = true;
    if (y%4 != 0)
        l = false;
    else if (y%100 != 0) 
        l = true;
    else if (y%400 != 0)
        l = false; 
    return l;      
    }    
    
Date
Date::next_Sunday (const Date &d) 
    {
    Date data(d.day, d.month, d.year);

    int my_day = data.Doomsday();

    std::cout << "The Weekday related to the date is " << day_name(my_day) << std::endl;

    data.add_days(7-my_day);
  
    return data;
    } 
    
Date
Date::next_Weekday (const Date &d)
    {
    Date data(d.day, d.month, d.year);

    int my_day = data.Doomsday();

    if (my_day == 5)
        {  //if it is Friday, the next_weekday is Monday
        data.add_days(3);
        std::cout << "The next Weekday is " << day_name(1) << std::endl;
        }
    else if (my_day == 6)
        {  //if it is Saturday, the next_weekday is Monday
        data.add_days(2);
        std::cout << "The next Weekday is " << day_name(1) << std::endl;
        }
    else
        {
        data.add_days(1);  //for every other day, the next_weekday is the following one
        std::cout << "The next Weekday is " << day_name(my_day+1) << std::endl;
        }
    
    return data;
    }        
    
// private methods 
    
int
Date::get_max (void) const
    {
    int max = 31;
    if (month==4 || month==6 || month==9 ||month==11) 
        max = 30;
    else if (month==2)
        {
        if (leap)
            max = 29;
        else
            max = 28;
        }
    return max;
    }    
    
int
Date::dooms_month (void) const 
    {
    int doom = 12;
    if (month == 1)
        doom = 24 + leap;
    if (month == 2)
        doom = 28 + leap;    
    if (month == 3)
        doom = 7;
    if (month == 4)
        doom = 4;
    if (month == 5)
        doom = 9;
    if (month == 6)
        doom = 6;
    if (month == 7)
        doom = 11;
    if (month == 8)
        doom = 8;
    if (month == 9)
        doom = 5;
    if (month == 10)
        doom = 10;
    if (month == 11)
        doom = 7;
    return doom;    
    } 
    
int
Date::Doomsday (void) const
    {
    // Step 1)
    int cbd, century;
    century = (year / 100) + 1 ;
    //cbd = century base day
    cbd = ( ( 5*century + ( (century-1) / 4 ) )% 7 +4 )%7;  

    // Step 2)
    int dooms, ldy;
    //ldy = last two digit of year
    ldy = year % 100;  
    //dooms = Doomsday of the year
    dooms = (ldy/12 + ldy%12 + (ldy%12)/4)%7 + cbd; 

    // Step 3)
    //ddm = Doomsday of the month
    int ddm = dooms_month(); 

    // Step 3.1)
    int dd = day - ddm;
    int dooms_day = dd + dooms;
    int my_day = dooms_day % 7;
    
    if (my_day < 0)
        my_day += 7;    

    return my_day;
    }  
    
std::string
Date::day_name (int d)
    {
    std::string name = "This number does not represent a day";
    if (d == 0)
        name = "Sunday";
    if (d == 1)
        name = "Monday";
    if (d == 2)
        name = "Tuesday";
    if (d == 3)
        name = "Wednesday";
    if (d == 4)
        name = "Thursday";
    if (d == 5)
        name = "Friday";
    if (d == 6)
        name = "Saturday";
    return name;                            
    }                     
