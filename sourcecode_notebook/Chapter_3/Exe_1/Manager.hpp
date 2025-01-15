#ifndef MANAGER_H
#define MANAGER_H

#include "Developer.hpp"

class Manager: public Developer {

protected:

    const double wsh_rate = 8.5;
    const double m_rate = 9.5;
    unsigned m_hours = 0;
    
public:
    
    Manager (const std::string& n, const std::string& sn, unsigned id): 
            Developer(n, sn, id) {}
    
    double salary_cal (void) const override 
    {
        return (work_hours - wsh_hours - m_hours) * pay_rate +
                          wsh_hours * wsh_rate +
                          m_hours * m_rate;                   
    }
        
    void set_m_hours (unsigned n) {m_hours = n;}

};

#endif /* MANAGER_H */
