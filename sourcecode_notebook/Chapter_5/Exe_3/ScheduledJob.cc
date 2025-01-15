#include "ScheduledJob.hh"

using namespace std;

Job::time_instant ScheduledJob::get_end_time() const
{
   return start_time + ptr -> get_execution_time();
}

void ScheduledJob::print() const
{
   ptr -> print();
   cout << " start_time " << start_time
      << " end_time " << get_end_time();
}

double ScheduledJob::evaluate() const
{
   return get_end_time() < ptr -> get_deadline()
      ? 0
      : ptr -> get_weight() * (static_cast<double>(get_end_time()) - static_cast<double>(ptr->get_deadline()));
}

Job::time_instant ScheduledJob::get_start_time() const
{
   return start_time;
}

void ScheduledJob::set_start_time (Job::time_instant st_time)
{
   start_time = st_time;
   adjust_start_time();
}

Job::time_instant ScheduledJob::get_deadline() const
{
   return ptr -> get_deadline();
}

Job::time_instant ScheduledJob::get_execution_time() const
{
   return ptr -> get_execution_time();
}

Job::time_instant ScheduledJob::get_submission_time() const
{
   return ptr -> get_submission_time();
}

void ScheduledJob::adjust_start_time (void)
{
   if (start_time < ptr -> get_submission_time())
      start_time = ptr -> get_submission_time();
}
