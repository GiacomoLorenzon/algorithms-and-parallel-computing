#ifndef PATIENT_HH
#define PATIENT_HH

#include "medicine.hpp"
#include <iostream>
#include <string>
#include <list>
#include <map>

class patient
{
    std::string name;

    //maps proposed_end_of_use date to medicine
    //it is a multimap since several medicines can
    //share the same proposed_end_of_use date
    std::multimap <Date, medicine> medicines;

  public:
    patient (const std::string &n): name(n) {}
    void add (const medicine& m);
    std::list<medicine> active_prescriptions (void) const;
};

#endif
