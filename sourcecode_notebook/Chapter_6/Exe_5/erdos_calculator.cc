#include "erdos_calculator.hh"

#include <limits>

namespace mathematicians
{
   constexpr std::size_t largest_erdos = std::numeric_limits<std::size_t>::max ();

   void erdos_calculator::add_author (std::shared_ptr<author> new_author)
   {
      const std::string & name = new_author -> get_name ();
      m_all_authors.insert ({name, new_author});
   }

   erdos_calculator::container_type::const_iterator erdos_calculator::find_closest_to_erdos (const container_type & authors)
   {
      container_type::const_iterator minimum_distance_author = authors.cbegin ();

      for (auto it = ++ authors.cbegin (); it != authors.cend (); ++it)
      {
         const auto & current_author = it -> second;

         if (current_author -> get_erdos_number () <
               minimum_distance_author -> second -> get_erdos_number ())
         {
            minimum_distance_author = it;
         }
      }

      return minimum_distance_author;
   }

   void erdos_calculator::compute_erdos_numbers (void)
   {
      container_type unvisited_authors = m_all_authors;

      for (const auto & pair : m_all_authors)
      {
         if (pair.first == "Erdos, Paul")
            pair.second -> set_erdos_number (0);
         else
            pair.second -> set_erdos_number (largest_erdos);
      }

      bool has_connections = true;

      while (not unvisited_authors.empty () and has_connections)
      {
         const auto current = find_closest_to_erdos (unvisited_authors);
         std::shared_ptr<author> current_author = current -> second;
         unvisited_authors.erase (current);

         if (current_author -> get_erdos_number () < largest_erdos)
         {
            const std::size_t neighbors_erdos_number =
               current_author -> get_erdos_number () + 1;

            for (auto coauthor : current_author -> get_coauthors ())
            {
               if (neighbors_erdos_number < coauthor -> get_erdos_number ())
                  coauthor -> set_erdos_number (neighbors_erdos_number);
            }
         }
         else has_connections = false;
      }
   }

   const erdos_calculator::container_type & erdos_calculator::get_all_authors (void) const
   {
      return m_all_authors;
   }
}
