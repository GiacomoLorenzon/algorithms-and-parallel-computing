#ifndef JOB_HH
#define JOB_HH

#include <iostream>

class Job
{
   public:
      typedef long int time_instant;
      typedef unsigned int id_type;

      Job (id_type j_id, time_instant sub_time, time_instant exe_time, time_instant dline, double w = 1.0) :
         id (j_id),
         submission_time (sub_time),
         execution_time (exe_time),
         deadline (dline),
         weight (w)
      {
         adjust_deadline();
      }

      time_instant get_deadline() const;
      time_instant get_execution_time() const;
      time_instant get_submission_time() const;
      id_type get_ID() const;

      double get_weight() const;

      void set_deadline (time_instant deadline);
      void set_execution_time (time_instant execution_time);
      void set_submission_time (time_instant submission_time);
      void set_weight (double weight);
      void print() const;

   private:
      id_type id;

      time_instant submission_time;
      time_instant execution_time;
      time_instant deadline;
      double weight;

      void adjust_deadline (void);
};

#endif /* JOB_H_ */
