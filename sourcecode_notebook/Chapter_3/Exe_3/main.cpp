#include <iostream>
#include <memory>

#include "Point.hpp"
#include "Interpolation.hpp"
#include "LinearInterpolation.hpp"
#include "StepwiseInterpolation.hpp"
#include "NearestNeighborInterpolation.hpp"

int
main (void)
{
  std::vector<Point> points {
    Point (1.0, 0.0),
      Point (2.0, 3.0),
      Point (3.0, 1.0),
      Point (4.0, 2.0),
      Point (5.0, 4.0)
      };

  double x = 5.0;
  //std::cin >> x;

  std::shared_ptr<Interpolation> method =
    std::make_shared<LinearInterpolation> (points);
  std::cout << method -> interpolate (x) << "\n";

  method = std::make_shared<StepwiseInterpolation> (points);
  std::cout << method -> interpolate (x) << "\n";

  method = std::make_shared<NearestNeighborInterpolation> (points);
  std::cout << method -> interpolate (x) << "\n";

  return 0;
}
