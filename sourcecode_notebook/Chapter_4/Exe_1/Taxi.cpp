#include "Taxi.hpp"

std::string Taxi::to_string (void) const
{
    std::string line1 = "Taxi " + id + " (" + zone + ")\n";

    std::string line2;
    if (driver)
        line2 = "\tDriver: " + driver->to_string() + "\n";
    else
        line2 = "\tNot assigned\n";

    return line1 + line2;
}