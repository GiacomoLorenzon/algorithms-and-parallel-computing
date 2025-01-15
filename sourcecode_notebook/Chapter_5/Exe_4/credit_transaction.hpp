#ifndef Credit_Transaction_HPP
#define Credit_Transaction_HPP

#include <iostream>
#include <utility>
#include <vector>

#include "date_util.hpp"

namespace fraud_detection
{
   class Credit_Transaction
   {
      private:
         /*The transaction date*/
         std::string date;

         /*The transaction amount*/
         double amount;

         /*The transaction address*/
         std::string address;

      public:

         /*Constructor*/
         Credit_Transaction (const std::string & dt, const double & e, const std::string & adrs) :
            date (dt),
            amount (e),
            address (adrs)
      {
         std::cout << "Credit_Transaction(" << dt << "," << e  << "," << adrs << ")" << std::endl;
      }

         const std::string & get_date (void) const;

         unsigned get_year (void) const;

         double get_amount (void) const;

         const std::string & get_address (void) const;
   };
}
#endif
