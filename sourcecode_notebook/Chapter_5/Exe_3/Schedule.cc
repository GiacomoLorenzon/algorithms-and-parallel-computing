#include "Schedule.hh"

Schedule::size_type Schedule::size (void) const
{
   return order.size();
}

double Schedule::evaluate() const
{
   double ret_val = 0;

   for (std::size_t i = 0; i < order.size(); ++i)
   {
      ret_val += order[i].evaluate();
   }

   return ret_val;
}

void Schedule::print() const
{
   for (std::size_t i = 0; i < order.size(); ++i)
   {
      order[i].print();
      std::cout << std::endl;
   }
}

void Schedule::add (const std::shared_ptr<Job> & j)
{
   // this is the first job
   if (order.empty())
      order.push_back (ScheduledJob (j));
   else
   {
      ScheduledJob sj (j, order.back().get_end_time());
      order.push_back (sj);
   }
}

// swap jobs at position i and j
void Schedule::swap (std::size_t i, std::size_t j)
{
   if (i >= order.size() || j >= order.size())
      return;

   using std::swap;
   swap (order[i], order[j]);
   validate();
}

void Schedule::validate()
{
   // guarantees that the schedule is valid,
   // i.e. a job starts after the end of the one before

   // This can be optimized, check only after min(i,j)

   //an empty schedule is ok
   if (order.empty())
      return;

   order[0].set_start_time (order[0].get_submission_time());
   ScheduledJob pred = order[0];

   for (std::size_t i = 1; i < order.size(); ++i)
   {
      // adjust current job start time
      order[i].set_start_time (std::max (pred.get_end_time(),
               order[i].get_submission_time()));
      pred = order[i];
   }
}
