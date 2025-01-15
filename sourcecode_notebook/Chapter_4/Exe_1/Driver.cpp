#include "Driver.hpp"

std::string Driver::to_string (void) const
{
    return (name + " " + surname + " (" + std::to_string(id) +")");
}