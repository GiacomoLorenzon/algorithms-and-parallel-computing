#include "Agency.hpp"

Agency::Agency (const std::vector<std::shared_ptr<Driver>>& ds, const std::vector<Taxi>& ts):
    drivers(ds), taxis(ts)
{}

void Agency::perform_assignment (void)
{
    if (taxis.size() <= drivers.size())
    {
        std::uniform_int_distribution<> distribution(0, drivers.size() - 1);
        unsigned initial_idx = distribution(generator);

        unsigned idx = initial_idx;
        for (Taxi &t : taxis) {
            if (idx == drivers.size())
                idx = 0;

            t.assign_driver(drivers[idx]);
            ++idx;
        }
    }
    else
      std::cerr << "ERROR: not enough drivers to perform the assignment" << std::endl;
}

void Agency::print (void) const
{
    for (const Taxi& t : taxis)
        std::cout << t.to_string() << std::endl;
}