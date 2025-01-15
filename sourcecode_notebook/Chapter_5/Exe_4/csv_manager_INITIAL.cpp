#include "csv_manager.hpp"
using namespace std;

namespace fraud_detection
{
   void
	 csv_manager::parse_files(std::vector<Tax_Payer> & payers)
   {
      //parses the tax payers csv file
      csv_manager::parse_csv(tax_payers_csv);
      csv_manager::create_payers(payers);
      //parses the cards csv file
      csv_manager::parse_csv(cards_csv);
      csv_manager::create_cards(payers);
      //parses the card transactions csv file
      csv_manager::parse_csv(card_transactions_csv);
      csv_manager::create_transactions(payers);
      //parses the card transactions csv file
      csv_manager::parse_csv(declarations_csv);
      csv_manager::create_declarations(payers);
   }

   void
	 csv_manager::parse_csv (const string & file_name)
   {

   }

   void
	 csv_manager::create_payers(std::vector<Tax_Payer> & payers)
   {

   }

   void
	 csv_manager::create_cards(std::vector<Tax_Payer> & payers)
      //Assumtion: the correspondig tax payers exist
   {
      for (const auto & row : fields)
      {
         int pos = find_payer(row[2], payers);
         if(pos != -1){
            Tax_Payer & p = payers[pos];
            Credit_Card c(row[0], row[1]);
            p.add_card(c);
         }
      }
   }

   void
	 csv_manager::create_transactions(std::vector<Tax_Payer> & payers)
      //Assumtion: the correspondig tax payers exist
   {
      for (const auto & row : fields)
      {
         std::string::size_type sz;
         double temp = std::stod (row[2], &sz);
         Credit_Transaction new_trs(row[1],temp,row[3]);
         for(Tax_Payer & p: payers)
         {
            const std::vector<Credit_Card>& cards = p.get_cards();
            bool stop = false;
            for (std::vector<Credit_Card>::const_iterator cit = cards.cbegin();
                 cit != cards.cend() && ! stop; ++cit)
            {
               if (cit->get_number() == row[0])
               {
                  p.append_transaction(cit->get_number(), new_trs);
                  stop = true;
               }
            }
         }
      }
   }

   void
	 csv_manager::create_declarations(std::vector<Tax_Payer> & payers)
      //Assumtion: the correspondig tax payers exist
   {
      Tax_Payer::declarations_vector all_declarations;
      for (const auto & row : fields)
      {
         int pos = find_payer(row[4], payers);
         if(pos != -1){
            Tax_Payer & tp = payers[pos];
            std::string::size_type sz;
            double temp = std::stod (row[3], &sz);
            pos = find_declaration(row[0], all_declarations);
            if(pos == -1){//if the declaration has not been created before
               Declaration d(row[0], row[1], row[2], temp);
               auto p = std::make_shared<Declaration> (d);
               all_declarations.push_back(p);
               tp.add_declaration(d);
            }
            else{//if the declaration has already been created for another tax payer
               Declaration & d = *all_declarations[pos];
               tp.add_declaration(d);
            }
         }
      }
   }

   int
	 csv_manager::find_payer(const std::string & name, const std::vector<Tax_Payer> & payers)
   {
      for(size_t i = 0; i < payers.size(); i++){
         Tax_Payer p = payers[i];
         if(p.get_name() == name)
            return i;
      }
      return -1;
   }

   int
	 csv_manager::find_declaration(const std::string & declaration_number,
		 const Tax_Payer::declarations_vector & declarations)
   {
      for(size_t i = 0; i < declarations.size(); i++){
         Declaration d = *declarations[i];
         if(d.get_number() == declaration_number)
            return i;
      }
      return -1;
   }
}
