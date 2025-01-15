#include <iostream>
#include <memory>

#include "Job.hh"
#include "ScheduledJob.hh"
#include "Schedule.hh"

using namespace std;

int main()
{
   //Job(id_type j_id, time_instant sub_time, time_instant exe_time, time_instant dline, double w =1.0):
   auto j1 = std::make_shared<Job> (0, 0, 1, 1, 2.0);
   auto j2 = std::make_shared<Job> (1, 0, 2, 2, 3.0);
   auto j3 = std::make_shared<Job> (2, 10, 4, 4);
   Schedule s;
   j1 -> print();
   cout << endl;
   j2 -> print();
   cout << endl;
   j3 -> print();
   cout << endl;
   cout << endl;
   s.add (j3);
   s.add (j2);
   s.add (j1);
   s.print();
   cout << "Total: " << s.evaluate() << endl << endl;
   std::size_t dim = 3;
   Schedule s_opt = s;
   double best_val = s.evaluate();
   bool improved = true;
   unsigned max_iterations = 10;
   cout << "Start Neigh exploration " << endl;
   s.print();
   cout << "Initial value " << best_val << endl;
   cout << endl;

   for (unsigned iter = 0; iter < max_iterations && improved; ++iter)
   {
      cout << "Iteration " << iter << endl << endl;
      Schedule current_best = s_opt;
      double current_best_val = best_val;
      improved = false;

      for (unsigned i = 0; i < dim - 1; ++i)
      {
         cout << "swap " << i << " " << i + 1 << endl;
         Schedule s_current = s_opt;
         s_current.swap (i, i + 1);
         cout << "Evaluating " << endl;
         s_current.print();
         cout << endl;
         const double current_val = s_current.evaluate();
         cout << "Value: " << current_val << endl;

         if (current_val < current_best_val)
         {
            cout << "Improving " << endl;
            current_best = s_current;
            improved = true;
            current_best_val = current_val;
            cout << "New best " << endl;
            current_best.print();
            cout << endl;
         }
      }

      std::swap (s_opt, current_best);
      best_val = current_best_val;
   }

   cout << "Final optimal solution found" << endl;
   s_opt.print();
   cout << endl;
   cout << "Total: " << s_opt.evaluate() << endl;
   return 0;
}
