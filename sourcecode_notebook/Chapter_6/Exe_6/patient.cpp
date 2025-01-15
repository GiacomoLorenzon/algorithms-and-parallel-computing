#include "patient.hpp"

void patient::add (const medicine& m)
{    
  //removing medicines whose proposed period of use is over
  auto beg = medicines.begin(), 
       lb = medicines.lower_bound(m.get_proposed_end_of_use_date());
  auto new_beg = medicines.erase(beg,lb);

  //removing incompatible or expired medicine
  auto i = new_beg;
  while (i != medicines.end()) {
    if (!m.compatible (i->second)) i = medicines.erase(i);
    else if (i->second.medicine_expiry()) i = medicines.erase(i);
    else i++;
  }

  //add new medicine if it is not already expired
  if (!m.medicine_expiry())
    medicines.insert(std::make_pair(m.get_proposed_end_of_use_date(), m));
}

std::list<medicine> patient::active_prescriptions (void) const
{
  std::list<medicine> l;
  for (auto i = medicines.begin(); i != medicines.end(); i++)
     l.push_back(i->second);
  return l;
}
