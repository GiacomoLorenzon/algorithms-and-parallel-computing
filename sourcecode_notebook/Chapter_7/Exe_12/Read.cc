#include "Read.hh"

namespace read
{
  std::vector<double>
  str_to_vec_double (std::string const& s, bool& ferr)
  {
    std::istringstream is{s};

    std::vector<double> coords;
    double d;
    while (is >> d)
      coords.push_back( d );

    if ( !is.eof() ) 
      ferr = true;         // if 'is' does NOT reach eof then there is a format error, even though
  // if ( is.fail() ) ferr = true;      // failbit is the right flag to use for such purposes,
                                        // but I get error at the end of every line.. (?)
    return coords;  
  }
  
  std::vector<Point> 
  read_table(std::string const& table, unsigned int& n, unsigned int& d);

}
