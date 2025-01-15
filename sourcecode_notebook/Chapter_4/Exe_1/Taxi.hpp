#ifndef TAXI_HH
#define TAXI_HH

#include <vector>
#include <memory>

#include "Receipt.hpp"
#include "Driver.hpp"

class Taxi {
  // identification number and zone
  const std::string id;
  const std::string zone;

  // pointer to the current driver
  std::shared_ptr<Driver> driver;
  
  // the receipts of the current week
  std::vector<Receipt> receipts;

public:
  // constructor
  Taxi (const std::string& i, const std::string& z): id(i), zone(z) {}

  void assign_driver (const std::shared_ptr<Driver>& d) {driver = d;}
  void save_receipt (const Receipt& r) {receipts.push_back(r);}

  std::string to_string (void) const;
};

#endif /* TAXI_HH */
