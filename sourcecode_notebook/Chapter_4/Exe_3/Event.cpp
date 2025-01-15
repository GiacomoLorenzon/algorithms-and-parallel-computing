#include "Event.h"

time_t Event::getTime (void) const 
{
    return date;
};

std::string Event::getName (void) const 
{
    return name;
};