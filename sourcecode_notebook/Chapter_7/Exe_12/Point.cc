#include <cmath>
#include <sstream>

#include "Point.hh"

double
Point::distance (const Point& p) const
{
  double dist = 0.0;

  for (size_type i = 0; i < x.size (); ++i)
    {
      const double delta = x[i] - p.x[i];
      dist += delta * delta;
    }

  return sqrt (dist);
}

std::string
Point::print (void) const
{
  std::ostringstream buffer;
  auto it = x.cbegin ();
  if (it != x.cend ())
    {
      buffer << *it++;
    }
  while (it != x.cend ())
    {
      buffer << " " << *it++;
    }
  buffer << std::endl;
  return buffer.str ();
}

double
Point::get_coord (size_type i) const
{
  return x[i];
}
