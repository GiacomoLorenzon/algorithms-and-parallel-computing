#include "Box.hpp"

// initialization of the static variable
unsigned Box::count = 0;

// memeber functions:

double Box::Volume() const
{
  return length * breadth * height;
}

// assignement operator
Box& Box::operator= (const Box &b) 
{
  std::cout << "Using assignement operator" << std::endl;
  length = b.length;
  breadth = b.breadth;
  height = b.height;
  
  return *this;
}
