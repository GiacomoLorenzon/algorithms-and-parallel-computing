#include "Stock_quote_archive.hpp"

void Stock_quote_archive::add_stock_quote (const Stock_quote & s)
{
  stock_quotes.insert (std::make_pair (s.get_symbol(), s));
}

void Stock_quote_archive::add_last_sale_price (const std::string & stock_symbol,
                                               float value)
{
  std::map<std::string, Stock_quote>::iterator it =
    stock_quotes.find (stock_symbol);

  if (it != stock_quotes.end())
    it->second.add_last_sale_price (value);
}

void Stock_quote_archive::print (void) const
{
  std::map<std::string, Stock_quote>::const_iterator it = stock_quotes.cbegin();

  while (it != stock_quotes.end())
    {
      it->second.print();
      ++it;
    }
}
