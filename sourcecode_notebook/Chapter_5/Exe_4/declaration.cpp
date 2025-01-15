#include "declaration.hpp"

namespace fraud_detection
{

   const std::string & Declaration::get_number (void) const
   {
      return number;
   }

   const std::string & Declaration::get_date (void) const
   {
      return date;
   }

   unsigned Declaration::get_year (void) const
   {
      return Date_Util::get_year_from_string(date);
   }

   double Declaration::get_amount (void) const
   {
      return amount;
   }

   const std::string & Declaration::get_tax (void) const
   {
      return tax;
   }

   std::string Declaration::INCOME_TAX = "income_tax";
   std::string Declaration::PROPERTY_TAX = "property_tax";

}
