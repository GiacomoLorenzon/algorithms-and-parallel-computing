#include "Agency.hpp"

int main (void)
{
    std::shared_ptr<Driver> d1 = std::make_shared<Driver>("Mike", "Kent", 111);
    std::shared_ptr<Driver> d2 = std::make_shared<Driver>("Anne", "Doyle", 222);
    std::shared_ptr<Driver> d3 = std::make_shared<Driver>("Bob", "Dylan", 333);

    Agency agency({d1, d2, d3}, {Taxi("A100", "Center-Z1"), Taxi("B200", "Suburb-Z8")});

    agency.perform_assignment();

    agency.print();
}