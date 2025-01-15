#include "NearestNeighborInterpolation.hpp"

#include "Point.hpp"

NearestNeighborInterpolation::NearestNeighborInterpolation
(const std::vector<Point> & points)
  : Interpolation (points) {}

double
NearestNeighborInterpolation::interpolate (double x) const
{
  double result (err_val);

  if (range_check (x))
    {
      std::vector<Point>::const_iterator previous = points.cbegin (),
        current = previous + 1;

      while (current != points.cend () and current -> get_x () < x)
        {
          ++current;
          ++previous;
        }

      if (current != points.cend ())
        {
          const double first_distance = x - previous -> get_x (),
            second_distance = current -> get_x () - x;
          const bool first_closest = second_distance > first_distance;
          result = first_closest ? previous -> get_y () : current -> get_y ();
        }
    }

  return result;
}
