#include "Centroid.hpp"

void
Centroid::update_coords (const std::vector<Point *> & ps)
{
  std::vector<double> new_coords(x.size(),0);

  for (std::size_t i = 0; i < ps.size (); ++i)
    {
      for (std::size_t j = 0; j < x.size (); ++j)
        new_coords[j] += ps[i] -> get_coord (j);
    }

  for (std::size_t j = 0; j < x.size (); ++j)
    new_coords[j] /= ps.size ();
  x.swap (new_coords);
}
