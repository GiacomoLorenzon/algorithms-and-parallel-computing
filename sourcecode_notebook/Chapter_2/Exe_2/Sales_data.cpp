#include "Sales_data.h"

using std::cout;
using std::cerr;
using std::endl;

Sales_data&
Sales_data::combine (const Sales_data &rhs)
{
    units_sold += rhs.units_sold;
    revenue += rhs.revenue;
    return *this;
}
    
double
Sales_data::avg_price () const 
{
    if (units_sold==0) 
      {
        cerr << "No books have been sold" << endl;
        return 0.0;
      }
    return revenue/units_sold;
}
    
void
Sales_data::print (void) const
{
    cout << "ISBN: " << bookNo << 
            " units_sold: " << units_sold <<
            " revenue: " << revenue << endl;
}        
