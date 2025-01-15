#ifndef DATAFRAME_H
#define DATAFRAME_H

#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

class DataFrame
{
public:
  typedef std::unordered_map<std::string, std::vector<double>> df_type;
  
  typedef df_type::key_type key_type;
  typedef df_type::value_type value_type;
  typedef df_type::mapped_type mapped_type;
  typedef mapped_type::size_type size_type;

private:
  df_type df_data;
  bool added_first_column;
  size_type n_rows;

  // return the names of columns in s separated by delim
  std::vector<key_type> split (const key_type & s, char delim) const;

  // returns true if column_name is valid (included in the constructor list)
  bool check_column_name (const key_type & column_name) const;

  // set a column data checking only right number of rows
  void set_column_data (const key_type & column_name,
                        const mapped_type & column_data);

public:
  explicit DataFrame (const key_type & c_names);
  DataFrame();

  mapped_type get_column (const key_type & column_name) const;

  double get_element_at (const key_type & column_name, 
                         size_type index) const;
  
  void set_element_at (const key_type & column_name, size_type index,
                       double value);

  double get_mean (const key_type & column_name) const;

  // set the values of an existing column
  void set_column (const key_type & column_name,
                   const mapped_type & column_data);

  // add a new column with data
  void add_column (const key_type & column_name,
                   const mapped_type & column_data);

  // return a copy of the DataFrame with rows i such 
  // that "c_name[i] == value"
  DataFrame select_equal (const key_type & c_name, 
                          double value) const;

  void print (void) const;
};

#endif //DATAFRAME_H
