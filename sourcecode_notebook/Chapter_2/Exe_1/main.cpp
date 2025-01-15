#include "Stock_quote.h"
#include "Stock_quote_archive.h"

int main()
{
  Stock_quote s1 ("AAPL");
  Stock_quote s2 ("GOOG");
  Stock_quote_archive archive;
  s1.add_last_sale_price (1);
  s2.add_last_sale_price (2);
  s1.print();
  s2.print();
  archive.add_stock_quote (s1);
  archive.add_stock_quote (s2);
  archive.print();
  archive.add_last_sale_price ("AAPL", 2);
  archive.add_last_sale_price ("GOOG", 1);
  archive.print();
  s1.print();
  s2.print();
  return 0;
}
