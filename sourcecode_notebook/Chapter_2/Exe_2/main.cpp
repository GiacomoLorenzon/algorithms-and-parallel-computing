#include "Sales_archive.h"

int main (void) {
    
    Sales_data sd1("1001", 10, 10);
    Sales_data sd2("1002", 10, 20);
    Sales_data sd3("1003", 10, 30);
    Sales_data sd4("1001", 10, 50);
    Sales_data sd5("1001", 10, 5);
    Sales_data sd6("1003", 10, 5);
    Sales_data sd7("1002", 10, 5);
    
    std::vector<Sales_data> v1 = {sd1,sd2,sd3,sd4,sd5,sd6,sd7};
    
    Sales_archive sa(v1);
    
    Sales_archive sn;
    
    sn = sa.reduce_by_book();
    
    sn.print_archive();
    
}
