#ifndef PLACE_HH
#define PLACE_HH

#include <vector>
#include <memory>

#include "comment.hh"

class place
{
   const std::string name;
   const std::string description;
   std::vector<std::shared_ptr<comment>> comments;

   public:
   place (std::string const & n, std::string const & desc)
      : name (n), description (desc) {}

   const std::vector<std::shared_ptr<comment>> & get_comments (void) const;

   void add_comment (std::shared_ptr<comment> cmnt);
};

#endif
