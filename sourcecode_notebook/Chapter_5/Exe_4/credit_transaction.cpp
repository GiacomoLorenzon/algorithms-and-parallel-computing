#include "credit_transaction.hpp"

namespace fraud_detection
{
   const std::string & Credit_Transaction::get_date (void) const
   {
      return date;
   }

   unsigned Credit_Transaction::get_year (void) const
   {
      return Date_Util::get_year_from_string(date);
   }

   double Credit_Transaction::get_amount (void) const
   {
      return amount;
   }

   const std::string & Credit_Transaction::get_address (void) const
   {
      return address;
   }
}
