#include <iostream>
#include <fstream>
#include <string>

#include "tax_payer.hpp"
#include "credit_transaction.hpp"
#include "credit_card.hpp"
#include "csv_manager.hpp"

using namespace std;
using namespace fraud_detection;

int main()
{
   std::vector<Tax_Payer> tax_payers;
   csv_manager csv_mgr ("data/tax_payers.csv", "data/cards.csv", "data/credit_trs.csv", "data/declarations.csv");
   csv_mgr.parse_files (tax_payers);

   for(const Tax_Payer & tp : tax_payers){
      if(tp.check_fraud(2017))
         cout << "Fraud detected with income declaration of user " << tp.get_name() << endl;
   }
   return 0;
}
