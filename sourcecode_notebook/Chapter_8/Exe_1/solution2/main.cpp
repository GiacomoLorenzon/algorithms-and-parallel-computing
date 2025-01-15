#include <iostream>
#include <vector>

#include "DataFrame.h"

int main()
{
  std::cout << "Test DataFrame" << std::endl;
  DataFrame<float> df ("c1 c2");
  DataFrame<double> df2 ("c1 c2");
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
  df.set_column ("c3", v1);
  df.print();
  std::vector<float> v_res = df.get_column ("c1");
  std::cout << "Printing v_res" << std::endl;

  for (size_t i = 0; i < v_res.size(); i++)
    std::cout << v_res[i] << " ";

  std::cout << std::endl;
  v_res = df.get_column ("c3");
  std::cout << "Printing v_res" << std::endl;

  for (size_t i = 0; i < v_res.size(); i++)
    std::cout << v_res[i] << " ";

  std::cout << std::endl;
  std::cout << df.get_mean ("c1") << std::endl;
  std::cout << df.get_mean ("c2") << std::endl;
  df.set_column ("c2", v2);
  std::vector<float> v3 = {4, 5};
  df.set_column ("c2", v3);
  std::cout << df.get_mean ("c2") << std::endl;
  std::cout << df.get_mean ("c3") << std::endl;
  std::cout << df.get_element_at ("c2", 1) << std::endl;
  std::cout << df.get_element_at ("c2", 4) << std::endl;
  std::cout << df.get_element_at ("c3", 1) << std::endl;
  df.set_element_at ("c2", 1, 27);
  std::cout << df.get_element_at ("c2", 1) << std::endl;
  df.add_column ("c3", v1);
  std::cout << "df after add" << std::endl;
  df.print();
  DataFrame<float> select_df = df.select_equal("c2", 1);
  std::cout << "select_df " <<  std::endl;
  select_df.print();

  return 0;
}
