#include <iostream>

#include "cl.hpp"

using std::cout;

template <typename T>
void f (cl<T> c1)
{
  cl<T> c2;
  c2 = c1; 
}

int main (void)
{
  cl<int> c; 
  f(c);
  cout << c.get_val() << '\n';
}
