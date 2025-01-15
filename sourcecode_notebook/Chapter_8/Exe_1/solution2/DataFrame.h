#ifndef DATAFRAME_H
#define DATAFRAME_H

#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

template<typename T>
class DataFrame
{
public:
  typedef std::unordered_map<std::string, std::vector<T> > df_type;
  
  typedef typename df_type::value_type value_type;
  typedef typename df_type::key_type key_type;
  typedef typename df_type::mapped_type mapped_type;
  typedef typename mapped_type::size_type size_type;

private:
  df_type df_data;

  // returns true if column_name is valid (included in the constructor list)
  bool check_column_name (const key_type & column_name) const;

  // return the names of columns in s separated by delim
  std::vector<key_type> split (const key_type & s, char delim) const;
  
  bool first_column_added;
  size_type n_rows;

  // set a column data checking only right number of rows
  void set_column_data (const key_type & column_name,
                        const mapped_type & column_data);

public:
  DataFrame (const key_type & c_names);

  DataFrame();

  DataFrame & operator= (const DataFrame &) = default;

  void print (void) const;

  void set_column (const key_type & column_name,
                   const mapped_type & column_data);

  mapped_type get_column (const key_type & column_name) const;

  T get_element_at (const key_type & column_name, size_type index) const;
  
  void set_element_at (const key_type & column_name, size_type index,
                       const T & value);

  T get_mean (const key_type & column_name) const;

  // add a new column with data
  void add_column (const key_type & column_name,
                   const mapped_type & column_data);

  // return a copy of the DataFrame with rows such that the c_name = value
  DataFrame<T> select_equal (const key_type & c_name, const T & value) const;
  
};  /*** end of class declaration ***/

template<typename T>
DataFrame<T>::DataFrame (const key_type & c_names)
  : DataFrame ()
{
  std::vector<key_type> columns_names = split (c_names, ' ');

  for (const key_type & name : columns_names)
    df_data[name];
}

template<typename T>
DataFrame<T>::DataFrame (void)
  : first_column_added (false), n_rows (0) {}

template<typename T>
bool DataFrame<T>::check_column_name (const key_type & column_name) const
{
  return df_data.find (column_name) != df_data.end();
}

template<typename T>
void DataFrame<T>::set_column (const key_type & column_name,
                               const mapped_type & column_data)
{
  if (check_column_name (column_name))
    set_column_data (column_name, column_data);
  else
    std::cerr << "Error, " << column_name << " is unknown" << std::endl;
}

template<typename T>
typename DataFrame<T>::mapped_type
DataFrame<T>::get_column (const key_type & column_name) const
{
  if (check_column_name (column_name))
    return df_data.at (column_name);
  else
    {
      std::cerr << "Error, " << column_name << " is unknown" << std::endl;
      return std::vector<T> ();
    }
}

template<typename T>
T DataFrame<T>::get_mean (const key_type & column_name) const
{
  if (check_column_name (column_name))
    {
      T sum = T();

      for (T d : df_data.at (column_name))
        sum += d;

      return sum / n_rows;
    }
  else
    {
      std::cerr << "Error, " << column_name << " is unknown" << std::endl;
      return std::numeric_limits<T>::quiet_NaN();
    }
}

template<typename T>
void DataFrame<T>::print (void) const
{
  for (const value_type & element : df_data)
    {
      std::cout << element.first << " :: ";

      for (const T & d : element.second)
        std::cout << d << " ";

      std::cout << std::endl;
    }
}

template<typename T>
std::vector<typename DataFrame<T>::key_type>
DataFrame<T>::split (const key_type & s,  char delim) const
{
  key_type word;
  std::vector<key_type> v;
  std::istringstream columns (s);

  while (std::getline (columns, word, delim)) v.push_back (word);

  return v;
}

template<typename T>
T DataFrame<T>::get_element_at (const key_type & column_name,
                                size_type index) const
{
  if (check_column_name (column_name))
    if (index < n_rows)
      return df_data.at (column_name)[index];
    else
      {
        std::cerr << "Error, index out of bound" << std::endl;
        return std::numeric_limits<T>::quiet_NaN();
      }
  else
    {
      std::cerr << "Error, " << column_name << " is unknown" << std::endl;
      return std::numeric_limits<T>::quiet_NaN();
    }
}

template<typename T>
void DataFrame<T>::set_element_at (const key_type & column_name,
                                   size_type index, const T & value)
{
  if (check_column_name (column_name))
    if (index < n_rows)
      df_data[column_name][index] = value;
    else
      std::cerr << "Error, index out of bound" << std::endl;
  else
    std::cerr << "Error, " << column_name << " is unknown" << std::endl;
}

template<typename T>
void DataFrame<T>::add_column (const key_type & column_name,
                               const mapped_type & column_data)
{
  if (! check_column_name (column_name))
    set_column_data (column_name, column_data);
  else
    std::cerr << "Error, " << column_name
              << " is already included in the DataFrame"
              << std::endl;
}

template<typename T>
void DataFrame<T>::set_column_data (const key_type & column_name,
                                    const mapped_type & column_data)
{
  if (! first_column_added)
    {
      n_rows = column_data.size();
      first_column_added = true;
      for (typename df_type::iterator it = df_data.begin(); 
                                      it != df_data.end(); it++)
        {  
          (it->second).resize(n_rows); 
        }
      df_data[column_name] = column_data;                               
    }
  else
    {
      // for next assignments check the column has the same number of rows
      if (n_rows == column_data.size())
        df_data[column_name] = column_data;
      else
        {
          std::cerr << "Error, " << column_name
                    << " has a different number of rows"
                    << std::endl;
        }
    }
}

template<typename T>
DataFrame<T> DataFrame<T>::select_equal (const key_type & c_name,
                                         const T & value) const
{
  if (! check_column_name (c_name))
    {
      std::cerr << "Error, " << c_name << " is unknown" << std::endl;
      return DataFrame<T> ();
    }

  std::vector<size_type> indexes; // solution indexes
  const mapped_type & relevant_column = df_data.at (c_name);

  // select rows indexes satisfying the selection criterion
  for (size_type i = 0; i < n_rows; ++i)
    if (relevant_column[i] == value)
      indexes.push_back (i);

  DataFrame<T> result;

  for (const value_type & element : df_data)
    {
      mapped_type v; //column values
      v.reserve (indexes.size ());

      // select proper column values
      for (size_type idx : indexes)
        v.push_back (element.second[idx]);

      result.add_column (element.first, v);
    }

  return result;
}

#endif //DATAFRAME_H
