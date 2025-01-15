#ifndef STOCKQUOTE_H
#define STOCKQUOTE_H

#include <vector>
#include <string>
#include <iostream>

class Stock_quote
{
  std::string symbol;
  std::vector<float> last_prices;

public:
  Stock_quote (const std::string & s): symbol (s) {}
  void add_last_sale_price (float value);
  void print (void) const;
  const std::string & get_symbol (void) const
  {
    return symbol;
  }
};

#endif //STOCKQUOTE_H
