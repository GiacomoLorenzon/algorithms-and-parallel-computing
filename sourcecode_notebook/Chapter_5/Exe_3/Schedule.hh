#ifndef SCHEDULE_HH
#define SCHEDULE_HH

#include <vector>
#include <memory>
#include <initializer_list>

#include "ScheduledJob.hh"

class Schedule
{
   private:
      std::vector<ScheduledJob> order;

      // guarantees that the schedule is valid, i.e. a job
      // starts after the end of the  one before
      void validate();

   public:
      typedef std::vector<ScheduledJob>::size_type size_type;

      Schedule() {};

      virtual ~Schedule() {};

      size_type size (void) const;

      // evaluate total weighted tardiness for the schedule;
      double evaluate() const;

      void print() const;
      void add (const std::shared_ptr<Job> & j);

      // swap jobs at position i and j
      void swap (std::size_t i, std::size_t j);
};

#endif /* SCHEDULE_H_ */
