#include <iostream>
#include <vector>

#include "user.hh"
#include "place.hh"
#include "comment.hh"

using namespace std;

int main()
{
   place p1 ("A", "restaurant");
   place p2 ("B", "cinema");
   user u("Mario","Rossi");
   user u2("Giulia","Bianchi");
   u.leave_a_comment ("it's a horrible place", p1);
   u.leave_a_comment ("better than Netflix and chill", p2);
   u2.leave_a_comment ("it's a horrible place again!", p1);

   for (auto c : p1.get_comments())
   {
      cout << c->get_text() << endl;
   }

   return 0;
}
