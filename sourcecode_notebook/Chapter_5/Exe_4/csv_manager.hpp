#ifndef csv_manager_hpp
#define csv_manager_hpp

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include "tax_payer.hpp"
#include "credit_transaction.hpp"
#include "credit_card.hpp"

namespace fraud_detection
{
   class csv_manager
   {
      private:
         /* The file names of the csv files with data about payers,
          * cards, card transactions, and declarations */
         std::string tax_payers_csv, cards_csv, card_transactions_csv, declarations_csv;

         /*A vector of vectors of strings used as data structure for the fields in the csv files*/
         std::vector<std::vector<std::string>> fields;

         /*Common method that parses the csv file formatted as text with ';' as field separators*/
         void parse_csv(std::string const&);

         /* Creates a vector of tax payer objects based on the fields from the parsed csv file
          * Receives: the vector of tax payer objects to be populated */
         void create_payers(std::vector<Tax_Payer> &);

         /* Creates vectors of card objects based on the fields from the parsed csv file
          * and adds them to their respective tax payer object
          * Receives: the vector of tax payer objects already populated */
         void create_cards(std::vector<Tax_Payer> &);

         /* Creates vectors of card objects based on the fields from the parsed csv file
          * and adds them to their respective tax payer object
          * Receives: the vector of tax payer objects already populated */
         void create_transactions(std::vector<Tax_Payer> &);

         /* Creates vectors of declaration objects based on the fields from the parsed csv file
          * and adds them to their respective tax payer object
          * Receives: the vector of tax payer objects already populated */
         void create_declarations(std::vector<Tax_Payer> &);

         /* Finds a specific tax payer by name from a vector of tax payers
          * Receives: the name of the payer to be found and the vector of tax payers
          * Returns: the index of the tax payer in the vector or -1 if not found*/
         int find_payer(std::string const&, std::vector<Tax_Payer> const&);

         /* Finds a specific declaration by number from a vector of declarations
          * Receives: the number of the declaration to be found and the vector of declarations
          * Returns: the index of the declaration in the vector or -1 if not found */
         int find_declaration(std::string const&, Tax_Payer::declarations_vector const&);

      public:
         /* Constructor
          * Receives: the file names of the three csv files */
         csv_manager(std::string const& t_p_csv, std::string const& c_csv, std::string const& c_t_csv, std::string const& d_csv) :
            tax_payers_csv(t_p_csv),
            cards_csv(c_csv),
            card_transactions_csv(c_t_csv),
            declarations_csv(d_csv){};

         /* Parses the csv files and populates a vector of tax payers along with each payer's
          * info, including credit cards and credit card transactions */
         void parse_files (std::vector<Tax_Payer> &);
   };
}

#endif
