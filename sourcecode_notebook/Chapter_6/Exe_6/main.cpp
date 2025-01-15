#include "medicine.hpp"
#include "patient.hpp"
#include "date.hpp"

#include <iostream>
#include <time.h>
#include <string>

using namespace std;
int main(int argc, char const *argv[]) {

  Date d1("2018-7-8");
    
  Date d2("2018-7-14");
    
  patient p("Aldo");

  //create a new medicine
  medicine m1 = medicine ("m1", d1, d2, 2, 3);
  medicine m2 = medicine ("m2", d1, d2, 1, 6);
  medicine m3 = medicine ("m3", d1, d2, 0, 7);
  medicine m4 = medicine ("m4", d1, d2, 8, 9);

  //add them to medicines of a patient
  p.add(m1);
  p.add(m2);
  p.add(m3);

  std::list<medicine> l = p.active_prescriptions();
  for (auto i = l.begin(); i != l.end(); i++) {
    std::cout << i->get_name() << '\n';
  }

  std::cout << "adding an element with incompatible range (m4)" << '\n';
  p.add(m4);
  //when m4 is added, others are deleted since they are not compatible with m4
  l = p.active_prescriptions();
  for (auto i = l.begin(); i != l.end(); i++) {
    std::cout << i->get_name() << '\n';
  }
  std::cout << "adding an already expired medicine (m5)" << '\n';
  medicine m5 = medicine ("m5", Date("2014-12-12"), d2, 5, 10);
  p.add(m5);
  l = p.active_prescriptions();
  for (auto i = l.begin(); i != l.end(); i++) {
    std::cout << i->get_name() << '\n';
  }

  return 0;
}
