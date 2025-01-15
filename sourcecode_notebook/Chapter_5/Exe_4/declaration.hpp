#ifndef DECLARE_HPP
#define DECLARE_HPP

#include <memory>
#include <iostream>
#include <vector>
#include <string>

#include "date_util.hpp"

namespace fraud_detection
{
   class Declaration
   {
      private:
         /*Declaration tax number*/
         std::string number;
         /*The type of declaration tax*/
         std::string tax;
         /*The date of the declaration*/
         std::string date;
         /*The declared amount*/
         double amount;

      public:
         /*Constructor*/
         Declaration(const std::string & n, const std::string & t, const std::string & d, const double & a) :
            number(n),
            tax(t),
            date(d),
            amount(a)
         {
            std::cout << "Declaration(" << n << "," << t << "," << d << "," << a << ")" << std::endl;
         }

         /*Public interface*/

         const std::string & get_number (void) const;

         const std::string & get_date (void) const;

         unsigned get_year (void) const;

         double get_amount (void) const;

         const std::string & get_tax (void) const;

         static std::string INCOME_TAX;
         static std::string PROPERTY_TAX;

   };
}

#endif
