#ifndef LINEAR_INTERPOLATION_HH
#define LINEAR_INTERPOLATION_HH

#include <vector>

#include "Interpolation.hpp"

class Point;

class LinearInterpolation : public Interpolation
{
public:
  explicit LinearInterpolation (const std::vector<Point> & points);
  virtual double interpolate (double x) const override;
};

#endif // LINEAR_INTERPOLATION_HH
