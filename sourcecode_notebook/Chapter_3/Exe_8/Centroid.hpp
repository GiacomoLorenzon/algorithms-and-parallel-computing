#ifndef CENTROID_H_
#define CENTROID_H_

#include <iostream>
#include <vector>

#include "Point.hpp"

class Centroid : public Point
{
public:
  Centroid (const std::vector<double>& coords)
    : Point (coords) {};
  
  void
  update_coords (const std::vector<Point *>&);
};

#endif /* CENTROID_H_ */
