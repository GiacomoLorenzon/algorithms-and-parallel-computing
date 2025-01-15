#ifndef POINT_H_
#define POINT_H_

#include <string>
#include <vector>

class Point
{
protected:
  std::vector<double> x;

public:
  typedef std::vector<double>::size_type size_type;

  Point (std::vector<double> const & coords)
    : x (coords) {};

  //compute distance to Point p
  double
  distance (const Point& p) const;
  std::string
  print (void) const;
  double
  get_coord(size_type i) const;
};

#endif /* POINT_H_ */
