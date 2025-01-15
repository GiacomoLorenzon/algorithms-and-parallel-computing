#include "Stock_quote_archive.h"

void Stock_quote_archive::print (void) const
{
  std::vector<Stock_quote>::const_iterator it = stock_quotes.cbegin();

  while (it != stock_quotes.cend())
    {
      it->print();
      ++it;
    }
}

void Stock_quote_archive::add_stock_quote (const Stock_quote & s)
{
  stock_quotes.push_back (s);
}


std::vector<Stock_quote>::iterator
Stock_quote_archive::find(const std::string & stock_symbol)
{
  bool found_symbol=false;

  std::vector<Stock_quote>::iterator it = stock_quotes.begin();

  while (it != stock_quotes.end() && ! found_symbol){
    if (it->get_symbol()==stock_symbol)
      found_symbol=true;
    else
      ++it;
  }
  return it;
}

void
Stock_quote_archive::add_last_sale_price (const std::string & stock_symbol,
                                               float value)
{
  std::vector<Stock_quote>::iterator it = find(stock_symbol);

  if (it != stock_quotes.end())
    it->add_last_sale_price (value);
}
