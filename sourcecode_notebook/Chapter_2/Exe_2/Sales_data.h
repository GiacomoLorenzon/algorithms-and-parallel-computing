#ifndef SALES_DATA_H
#define SALES_DATA_H

#include <iostream>
#include <string>

class Sales_data {

public:
    // constructors:
    Sales_data (void) = default;
    Sales_data (const std::string &bn, unsigned u, double r):
        bookNo(bn), units_sold(u), revenue(r) {}  
    // getters:      
    std::string isbn (void) const {return bookNo;}
    unsigned get_units_sold (void) const {return units_sold;}
    double get_revenue (void) const {return revenue;}
    // combine
    Sales_data& combine (const Sales_data &);
    // average price
    double avg_price (void) const;
    // print
    void print (void) const;

private:
    std::string bookNo = "";
    unsigned units_sold = 0;
    double revenue = 0.0;    

};

#endif /* SALES_DATA_H */
