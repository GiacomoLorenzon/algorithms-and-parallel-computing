#ifndef AGENCY_HH
#define AGENCY_HH

#include "Taxi.hpp"

#include <random>
#include <iostream>

class Agency {

private:
    std::vector<std::shared_ptr<Driver>> drivers;
    std::vector<Taxi> taxis;

    std::default_random_engine generator;

public:
    Agency (const std::vector<std::shared_ptr<Driver>>&, const std::vector<Taxi>&);

    void perform_assignment (void);

    void print (void) const;
};

#endif //TAXISYSTEM_AGENCY_H
