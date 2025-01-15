#include "medicine.hpp"
#include <ctime>
#include <iostream>
#include <string>

std::pair <unsigned, unsigned> medicine::get_compatibility_range (void) const
{
  return compatibility_range;
}

std::string medicine::get_name (void) const
{
  return name;
}

Date medicine::get_expiration_date (void) const
{
  return expiration_date;
}

Date medicine::get_proposed_end_of_use_date (void) const
{
  return proposed_end_of_use;
}

bool medicine::compatible (const medicine &m) const
{
  return !(m.compatibility_range.first > this->compatibility_range.second ||
          m.compatibility_range.second < this->compatibility_range.first);        
}

bool medicine::medicine_expiry (void) const
{
  /*creates a date from now and compares it with expiration date*/
   time_t now = time(0);
   struct tm  tstruct;
   char *buf = new char[80];
   tstruct = *localtime(&now);
   strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
   std::string s (buf, buf+10);
   Date d = Date(s);
   delete []buf;
   return (expiration_date < d);
}
