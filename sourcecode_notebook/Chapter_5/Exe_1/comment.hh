#ifndef COMMENT_HH
#define COMMENT_HH

#include <string>

class comment
{
   const std::string text;
   public:
   comment (const std::string & txt): text (txt) {}

   const std::string & get_text() const;
};

#endif
