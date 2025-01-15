#ifndef USER_HH
#define USER_HH

#include "comment.hh"
#include "place.hh"

class user
{
   const std::string name;
   const std::string surname;
   std::vector<std::shared_ptr<comment>> comments;

   public:
   user (const std::string &n, const std::string &s):
      name(n), surname(s) {}

   void leave_a_comment (std::string const &, place &);
};

#endif
