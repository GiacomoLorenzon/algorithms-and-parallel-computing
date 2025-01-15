#ifndef ERDOS_CALCULATOR_HH
#define ERDOS_CALCULATOR_HH

#include <map>
#include <memory>
#include <string>

#include "author.hh"

namespace mathematicians
{
   class erdos_calculator
   {
      public:
         typedef std::map< std::string, std::shared_ptr<author> > container_type;

      private:
         container_type m_all_authors;

         static container_type::const_iterator find_closest_to_erdos (const container_type &);

      public:
         void add_author (std::shared_ptr<author>);

         void compute_erdos_numbers (void);

         const container_type & get_all_authors (void) const;
   };
}

#endif // ERDOS_CALCULATOR_HH
