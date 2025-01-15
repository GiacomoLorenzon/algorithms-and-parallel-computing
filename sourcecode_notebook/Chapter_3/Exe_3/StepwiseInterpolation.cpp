#include "StepwiseInterpolation.hpp"

#include "Point.hpp"

StepwiseInterpolation::StepwiseInterpolation (const std::vector<Point> & points)
  : Interpolation (points) {}

double
StepwiseInterpolation::interpolate (double x) const
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
          result = previous -> get_y ();
        }
    }

  return result;
}
