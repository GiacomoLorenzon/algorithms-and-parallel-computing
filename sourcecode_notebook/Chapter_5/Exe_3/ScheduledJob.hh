#ifndef SCHEDULEDJOB_HH
#define SCHEDULEDJOB_HH

#include <memory>

#include "Job.hh"

class ScheduledJob
{
   private:
      std::shared_ptr<Job> ptr;
      Job::time_instant start_time;

      void adjust_start_time (void);

   public:
      ScheduledJob (const std::shared_ptr<Job> & j_ptr, Job::time_instant st_time):
         ptr (j_ptr),
         start_time (st_time)
      {
         adjust_start_time();
      }

      ScheduledJob (Job j, Job::time_instant st_time):
         ptr (std::make_shared<Job> (j)),
         start_time (st_time)
      {
         adjust_start_time();
      }

      explicit ScheduledJob (const std::shared_ptr<Job> & j_ptr) :
         ptr (j_ptr),
         start_time (j_ptr->get_submission_time())
      {}

      Job::time_instant get_end_time() const;

      Job::time_instant get_start_time() const;

      void set_start_time (Job::time_instant  st_time);

      void print() const;

      double evaluate() const;

      Job::time_instant get_deadline() const;

      Job::time_instant get_execution_time() const;

      Job::time_instant get_submission_time() const;
};

#endif /* SCHEDULEDJOB_H_ */
