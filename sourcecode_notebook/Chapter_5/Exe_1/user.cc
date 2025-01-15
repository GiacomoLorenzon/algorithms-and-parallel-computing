#include "user.hh"

void user::leave_a_comment (std::string const & txt, place & p)
{
   std::shared_ptr<comment> c = std::make_shared<comment> (txt);
   comments.push_back (c);
   p.add_comment (c);
}
