#ifndef INTERPOLATION_HH
#define INTERPOLATION_HH

#include <limits>
#include <vector>

#include "Point.hpp"

class Interpolation
{
protected:
  std::vector<Point> points; // sorted_vector
  constexpr static double err_val = std::numeric_limits<double>::quiet_NaN();

public:
  virtual double interpolate (double) const = 0;
  bool range_check (double) const;

  Interpolation (const std::vector<Point> &);
  virtual ~Interpolation (void) = default;
};

#endif // INTERPOLATION_HH
