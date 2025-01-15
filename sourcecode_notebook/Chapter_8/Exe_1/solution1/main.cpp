#include <iostream>
#include <vector>

#include "DataFrame.hh"

int main()
{
  std::cout << "Test DataFrame" << std::endl;
  DataFrame<float> df ("c1 c2");
  /*    df.test_check("c1");
        df.test_check("c2");
        df.test_check("c3");
  */
  df.print();
  std::vector<float> v1 = {1, 2, 3};
  std::vector<float> v2 = {4, 5, 6};
  df.set_column ("c1", v1);
  df.set_column ("c2", v2);
  df.set_column ("c2", v1);
  df.print();
  std::vector<float> v_res = df.get_column ("c1");
  std::cout << "Printing v_res" << std::endl;
  
  auto mm = df.get_mean("c1");
  std::cout << "mean: " << mm << std::endl;
  
  return 0;
}
