#ifndef STOCKQUOTEARCHIVE_H
#define STOCKQUOTEARCHIVE_H

#include <map>

#include "Stock_quote.hpp"

class Stock_quote_archive
{
  std::map<std::string, Stock_quote> stock_quotes;
public:
  void add_stock_quote (const Stock_quote & s);
  void add_last_sale_price (const std::string & stock_symbol, float value);
  void print (void) const;
};

#endif //STOCKQUOTEARCHIVE_H
