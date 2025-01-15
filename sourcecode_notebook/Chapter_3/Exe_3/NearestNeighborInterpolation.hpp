#ifndef NEAREST_NEIGHBOR_INTERPOLATION_HH
#define NEAREST_NEIGHBOR_INTERPOLATION_HH

#include <vector>

#include "Interpolation.hpp"

#include "Point.hpp"

class NearestNeighborInterpolation: public Interpolation
{
public:
  explicit NearestNeighborInterpolation (const std::vector<Point> &);

  double interpolate (double) const override;
};

#endif // NEAREST_NEIGHBOR_INTERPOLATION_HH
