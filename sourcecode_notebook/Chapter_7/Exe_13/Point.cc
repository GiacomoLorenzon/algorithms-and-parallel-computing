#include <cmath>
#include <iostream>

#include "Point.hh"

double Point::distance (const Point & p) const
{
  double dist = 0.0;

  for (std::size_t i = 0; i < x.size (); ++i)
    {
      const double delta = x[i] - p.x[i];
      dist += delta * delta;
    }

  return sqrt (dist);
}

void Point::print (void) const
{
  for (auto it = x.begin (); it != x.end (); ++it)
    {
      std::cout << *it;
      std::cout << " ";
    }

  std::cout << std::endl;
}

double Point::get_coord (std::size_t i) const
{
  return x[i];
}


void Point::set_coord (std::size_t i, double val)
{
  x[i] = val;
}

Point::coords_type Point::get_coords (void) const
{
  return x;
}

double Point::euclidean_norm (void) const
{
  static const std::vector<double> zero_vector (x.size (), 0.);
  static const Point origin (zero_vector);
  return distance (origin);
}

double Point::infinity_norm (void) const
{
  double max_value = std::abs (x[0]);

  for (std::size_t i = 1; i < x.size (); ++i)
    {
      const double next = std::abs (x[i]);
      if (next > max_value) max_value = next;
    }

  return max_value;
}

std::size_t Point::get_n_dimensions (void) const
{
  return x.size ();
}
