#ifndef _KMEANS_READ_HH_
#define _KMEANS_READ_HH_

#include "Point.hh"

#include <vector>
#include <string>
#include <fstream>
#include <sstream>

namespace read
{
  std::vector<double>
  str_to_vec_double (std::string const&, bool&);

  std::vector<Point> 
  read_table(std::string const&, unsigned int&, unsigned int&);
}

#endif  // _KMEANS_READ_HH_
