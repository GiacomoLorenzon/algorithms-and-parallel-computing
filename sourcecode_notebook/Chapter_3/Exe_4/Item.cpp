#include <iostream>

#include "Item.hpp"

double Item::get_size (void) const
{
  return size;
}

double Item::get_weight (void) const
{
  return weight;
}

void Item::set_size (double s)
{
  size = s;
}

void Item::set_weight (double w)
{
  weight = w;
}

void Item::set_value (double v)
{
  value = v;
}

void Item::print (void) const
{
  std::cout << " size: " << size
            << " weight: " << weight
            << " value: " << value;
}
