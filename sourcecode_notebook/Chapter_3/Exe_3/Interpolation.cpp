#include "Interpolation.hpp"

#include "Point.hpp"

bool
Interpolation::range_check (double x) const
{
  return not (x < points.front().get_x() or x > points.back().get_x());
}

Interpolation::Interpolation (const std::vector<Point> & points)
  : points (points) {}
