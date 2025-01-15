#ifndef RECEIPT_HH
#define RECEIPT_HH

#include "Date.hpp"

class Receipt {

  std::string address;
  Date date;
  double price;

public:
  Receipt (const std::string & a, const Date &d, double p):
    address (a), date(d), price (p) {}

};

#endif /* RECEIPT_HH */
