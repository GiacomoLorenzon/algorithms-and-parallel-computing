#include "Calendar.h"

void Calendar::addEvent (const Event &event)
{
    events->push_back(event);
}

void Calendar::print() const 
{
    for (const Event &e : *events)
        std::cout << e.getName() << std::endl;
}
