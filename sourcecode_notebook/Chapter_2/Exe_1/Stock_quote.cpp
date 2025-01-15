#include "Stock_quote.h"

void Stock_quote::add_last_sale_price (float value)
{
  last_prices.push_back (value);
}

void Stock_quote::print (void) const
{
  std::cout << symbol << std::endl;

  for (const float val : last_prices)
    std::cout << val << std::endl;
}
