#include "LinearInterpolation.hpp"

#include "Point.hpp"

LinearInterpolation::LinearInterpolation (const std::vector<Point> & points)
  : Interpolation (points) {}

double
LinearInterpolation::interpolate (double x) const
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
          const double
            x1 (previous -> get_x ()), x2 (current -> get_x ()),
            y1 (previous -> get_y ()), y2 (current -> get_y ());
          result = y1 + (y2 - y1) * (x - x1) / (x2 - x1);
        }
    }

  return result;
}
