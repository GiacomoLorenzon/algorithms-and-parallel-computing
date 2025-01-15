#include "place.hh"

const std::vector<std::shared_ptr<comment>> & place::get_comments (void) const
{
   return comments;
}

void place::add_comment (std::shared_ptr<comment> cmnt)
{
   comments.push_back (cmnt);
}
