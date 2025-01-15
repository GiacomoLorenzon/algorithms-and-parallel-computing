#ifndef DATAFRAME_HH
#define DATAFRAME_HH

#include <sstream>
#include <iostream>
#include <string>
#include <vector>

class DataFrame
{
public:
  typedef std::vector<std::string> key_container;
  
  typedef key_container::value_type key_type;
  typedef std::vector<double> mapped_type;
  typedef mapped_type::size_type size_type;

private:
  key_container df_keys;
  std::vector<mapped_type> df_values;
  bool added_first_column;

  // return the names of columns in s separated by delim
  key_container split (const key_type & s, char delim) const;

  // return the index of column key, or df_keys.size () if not found
  size_type look_up (const key_type & key) const;

public:
  explicit DataFrame (const key_type & c_names);
  explicit DataFrame (const key_container & names);

  const mapped_type & get_column (const key_type & column_name) const;

  double get_element_at (const key_type & column_name, 
                         size_type index) const;

  void set_element_at (const key_type & column_name, size_type index,
                       double value);

  double get_mean (const key_type & column_name) const;

  // add a new column with data
  void set_column (const key_type & column_name,
                   const mapped_type & column_data);

  // return a copy of the DataFrame with rows i such 
  // that "c_name[i] == value"
  DataFrame select_equal (const key_type & c_name,
                          double value) const;

  void print (void) const;
};

#endif // DATAFRAME_HH
