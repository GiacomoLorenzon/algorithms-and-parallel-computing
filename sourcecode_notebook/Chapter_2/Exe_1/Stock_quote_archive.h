#ifndef STOCKQUOTEARCHIVE_H
#define STOCKQUOTEARCHIVE_H

#include "Stock_quote.h"

class Stock_quote_archive
{
  std::vector<Stock_quote> stock_quotes;
  std::vector<Stock_quote>::iterator find(const std::string & stock_symbol);

public:
  void add_stock_quote (const Stock_quote & s);
  void print (void) const;
  void add_last_sale_price (const std::string & stock_symbol, float value);
};

#endif //STOCKQUOTEARCHIVE_H
