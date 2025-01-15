#include "credit_card.hpp"

namespace fraud_detection
{
   const std::string & Credit_Card::get_expiry_date (void) const
   {
      return expiry_date;
   }

   const std::string & Credit_Card::get_number (void) const
   {
      return number;
   }

   const Credit_Card::transactions_vector &  Credit_Card::get_transactions (void) const
   {
      return transactions;
   }

   void Credit_Card::add_transaction(const Credit_Transaction & new_trs)
   {
      auto p = std::make_shared<Credit_Transaction>(new_trs);
      this->transactions.push_back(p);
   }

   double Credit_Card::get_trs_amount (unsigned year) const
   {
      double total = 0;
      for (const auto & transaction: transactions)
      {
         unsigned transaction_year = Date_Util::get_year_from_string(transaction->get_date());
         if (year ==  transaction_year)
            total += transaction->get_amount();
      }
      return total;
   }
}
