#ifndef TAX_PAYER_HPP_
#define TAX_PAYER_HPP_

#include <iostream>
#include <vector>
#include <string>
#include <memory>

#include "credit_card.hpp"
#include "declaration.hpp"

namespace fraud_detection
{
   class Tax_Payer
   {
      public:
         typedef std::vector <std::shared_ptr <Declaration>> declarations_vector;

      private:
         /*Tax payer's name*/
         std::string name;
         /*Tax payer's birth place*/
         std::string birth_place;
         /*Tax payer's current address */
         std::string current_address;
         /*Tax payer's credit cards*/
         std::vector <Credit_Card> cards;
         /*Tax payer's old addresses*/
         std::vector<std::string> old_addresses;

         /*Tax payer's declarations.
           One declaration may be shared by multiple tax payers
           E.g.: wife and husband may share a declaration*/
         declarations_vector declarations;

      public:
         /*Constructor*/
         Tax_Payer(const std::string & s1, const std::string & s2, const std::string & s3) :
            name(s1),
            birth_place(s2),
            current_address(s3)
         {
            std::cout << "Tax_Payer(" << s1 << "," << s2 << "," <<  s3 << ")" << std::endl;
         }

         /*Public interface*/
         const std::string & get_name (void) const;

         const std::string & get_birth_place (void) const;

         const std::string & get_current_address (void) const;

         const std::vector<std::string> & get_old_addresses (void) const;

         /* Adds current address to the old addresses vector and
          * replaces the current address with a new address
          */
         void update_address(const std::string &);

         const declarations_vector & get_declarations (void) const;

         /*Adds a declaration to the declarations vector*/
         void add_declaration(const Declaration &);

         const std::vector <Credit_Card> & get_cards (void) const;

         void add_card(const Credit_Card &);

         /* Finds a card by name among the vector of cards of this tax payer
          * Receives: the name of the card to be found
          * Returns: the found card's index in the vector or -1 if not found */
         int find_card(const std::string &) const;

         /* Appens a transaction to a given credit card from the tax payer
          * Receives: the name of the credit card and the transaction to be appended*/
         void append_transaction(const std::string &, const Credit_Transaction &);

         /* Checks for a fraud in a specific year
          * A fraud is detected for a tax payer if his/her credit card expenses,
          * in a specific fiscal year, were more than 10% of the total income taxes they have payed
          * Receives: the fiscal year
          */
         bool check_fraud(unsigned) const;

         /* Gets the amount from the declared income tax of a given year for this tax payer
          * Receives: the year of the income declaration
          * Returns: the amount of the income declaration for the year
          */
         double get_declared_year_income(unsigned) const;

         /* Gets the total amount of all credit transactions of a given year for this tax payer
          * Receives: the year of the income
          * Returns: the total amount of all credit transactions of a given year
          */
         double get_year_transaction_amout(unsigned) const;
   };
}

#endif
