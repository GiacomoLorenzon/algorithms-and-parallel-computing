#ifndef CREDIT_CARD_HPP
#define CREDIT_CARD_HPP

#include "credit_transaction.hpp"
#include "date_util.hpp"

#include <iostream>
#include <vector>
#include <memory>
#include <utility>

namespace fraud_detection
{
   class Credit_Card
   {
      typedef std::vector <std::shared_ptr <Credit_Transaction>> transactions_vector;

      std::string number;
      std::string expiry_date;
      transactions_vector transactions;

      public:

      /*Constructor*/
      Credit_Card(const std::string & s, const std::string & d):number(s), expiry_date(d)
      {
         std::cout << "Card(" << s << "," << d << ")" << std::endl;
      }

      /*Public interface*/

      const std::string & get_expiry_date (void) const;

      const std::string & get_number (void) const;

      const transactions_vector & get_transactions (void) const;

      /*Adds a transaction to the transactions vector*/
      void add_transaction(const Credit_Transaction & new_trs);

      /* Returns the total amount of all transactions in a specific date
       * Receives: the date of the transactions
       * Returns: the total amount of transactions in the specific date */
      double get_trs_amount (unsigned year) const;
   };
}
#endif
