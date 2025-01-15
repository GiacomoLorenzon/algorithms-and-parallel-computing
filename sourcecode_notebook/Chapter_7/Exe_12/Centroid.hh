#ifndef CENTROID_H_
#define CENTROID_H_

#include <vector>

#include "Point.hh"

class Centroid : public Point
{
public:
  typedef Point::size_type size_type;

  Centroid (std::vector<double> const & coords)
    : Point (coords) {};

  void
  update_coords (std::vector<Point *> const &);
};

#endif /* CENTROID_H_ */
