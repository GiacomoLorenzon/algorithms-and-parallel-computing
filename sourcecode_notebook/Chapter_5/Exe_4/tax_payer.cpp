#include "tax_payer.hpp"
#include <string>

namespace fraud_detection
{
   const std::string & Tax_Payer::get_name (void) const
   {
      return name;
   }

   const std::string & Tax_Payer::get_birth_place (void) const
   {
      return birth_place;
   }

   const std::string & Tax_Payer::get_current_address (void) const
   {
      return current_address;
   }

   void Tax_Payer::update_address (const std::string & new_address)
   {
      old_addresses.push_back (current_address);
      current_address = new_address;
   }

   std::vector<std::string> const & Tax_Payer::get_old_addresses (void) const
   {
      return old_addresses;
   }

   Tax_Payer::declarations_vector const & Tax_Payer::get_declarations (void) const
   {
      return declarations;
   }

   void Tax_Payer::add_declaration (const Declaration & d)
   {
      auto p = std::make_shared<Declaration> (d);
      this->declarations.push_back (p);
   }

   const std::vector<Credit_Card> & Tax_Payer::get_cards (void) const
   {
      return cards;
   }

   void Tax_Payer::add_card (const Credit_Card & c)
   {
      cards.push_back (c);
   }

   int Tax_Payer::find_card(const std::string & card_number) const{
      for(size_t i = 0; i < cards.size(); i++){
         Credit_Card card = cards[i];
         if(card.get_number() == card_number)
            return static_cast<int>(i);
      }
      return -1;
   }

   void Tax_Payer::append_transaction(const std::string & card_number, const Credit_Transaction & transaction)
   {
      int pos = find_card(card_number);
      if(pos != -1){
         Credit_Card & card = cards[static_cast<size_t>(pos)];
         card.add_transaction(transaction);
      }
   }

   bool Tax_Payer::check_fraud(unsigned year) const
   {

      double total_year_transaction_amout = get_year_transaction_amout(year);
      std::cout << "Total Year Credit Transaction Amount: " << total_year_transaction_amout << std::endl;
      double declared_year_income = get_declared_year_income(year);
      std::cout << "Declared Income: " << declared_year_income << std::endl;
      double ratio = 100 * total_year_transaction_amout / declared_year_income;
      std::cout << "Ratio: " << ratio << "%" << std::endl;
      return ratio > 10;
   }

   double Tax_Payer::get_declared_year_income(unsigned year) const
   {
      for(auto & d : declarations)
      {
         if( d->get_year() == year &&
               d->get_tax() == Declaration::INCOME_TAX)
            return d->get_amount();
      }
      return 0;
   }

   double Tax_Payer::get_year_transaction_amout(unsigned year) const
   {
      double total_year_amout = 0;
      for(Credit_Card card : cards)
         total_year_amout += card.get_trs_amount(year);
      return total_year_amout;
   }
}
