#ifndef CALENDAR_H
#define  CALENDAR_H

#include <iostream>
#include <vector>
#include <memory>

#include "Event.h"

class Calendar {

private:
    std::shared_ptr<std::vector<Event>> events;

public:
    Calendar (void): events(std::make_shared<std::vector<Event>>()) {}
    void addEvent (const Event&);
    void print (void) const;
};

#endif // CALENDAR_H