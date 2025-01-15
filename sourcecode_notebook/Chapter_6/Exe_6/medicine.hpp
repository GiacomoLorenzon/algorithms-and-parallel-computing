#ifndef MEDICINE_HH
#define MEDICINE_HH

#include "date.hpp"

class medicine
{
  std::string name;
  Date expiration_date;
  Date proposed_end_of_use;

  /* assuming that each medicine has an assigned range. Other medicines
  are considered  compatible if they have an overlapping range,
  and incompatible otherwise*/
  std::pair <unsigned, unsigned> compatibility_range;

public:
  /*the constructor*/
  medicine(const std::string& s, const Date& e_d, const Date& p_d, unsigned p1, unsigned p2): 
    name(s), expiration_date(e_d), proposed_end_of_use(p_d), 
    compatibility_range(std::make_pair(p1,p2))
    {}

  /*returns the compatibility range */
  std::pair <unsigned, unsigned> get_compatibility_range (void) const;

  /*returns the name of the medicine */
  std::string get_name (void) const;

  /*returns the expiration date */
  Date get_expiration_date (void) const;

  /*returns the proposed_end_of_use date */
  Date get_proposed_end_of_use_date (void) const;

  /*returns true if m has overlapping compatibility range with this */
  bool compatible (const medicine &m) const;

  /*returns true if the medicine is expired */
  bool medicine_expiry (void) const;
};

#endif
