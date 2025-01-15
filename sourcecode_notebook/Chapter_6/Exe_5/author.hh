#ifndef AUTHOR_HH
#define AUTHOR_HH

#include <limits>
#include <memory>
#include <string>
#include <vector>

namespace mathematicians
{
   class author
   {
      private:
         std::string m_name;
         std::string m_affiliation;
         std::vector< std::shared_ptr<author> > m_coauthors;
         std::size_t m_erdos_number = std::numeric_limits<std::size_t>::max ();

      public:
         author (void) = delete;
         explicit author (const std::string & name);
         author (const std::string & name, const std::string & affiliation);

         const std::string & get_name (void) const;

         const std::string & get_affiliation (void) const;

         const std::vector< std::shared_ptr<author> > & get_coauthors (void) const;

         std::size_t get_erdos_number (void) const;

         void set_affiliation (const std::string &);
         void add_coauthor (const std::shared_ptr<author> &);
         void set_erdos_number (std::size_t);
   };
}

#endif // AUTHOR_HH
