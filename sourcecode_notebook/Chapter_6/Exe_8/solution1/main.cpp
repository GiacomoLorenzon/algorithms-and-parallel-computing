#include <iostream>
#include <vector>

#include "DataFrame.hpp"

int main()
{
  std::cout << "Test DataFrame" << std::endl;
  DataFrame df ("c1 c2");
  df.print();
  std::cout << std::endl;

  std::vector<double> v1 = {1, 2, 3};
  std::vector<double> v2 = {4, 5, 6};
  df.set_column ("c1", v1);
  df.set_column ("c2", v2);
  df.set_column ("c2", v1);
  df.print();
  std::cout << std::endl;
  
  std::vector<double> v_res = df.get_column ("c1");
  std::cout << "Printing v_res" << std::endl;
  
  auto mm = df.get_mean("c1");
  std::cout << "mean: " << mm << std::endl;
  
  return 0;
}
