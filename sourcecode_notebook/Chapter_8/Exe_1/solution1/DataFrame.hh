#ifndef DATAFRAME_HH
#define DATAFRAME_HH

#include <sstream>
#include <string>
#include <vector>

template <typename T>
class DataFrame
{
public:
  typedef std::vector<std::string> key_container;
  typedef std::vector<T> mapped_container;

  typedef key_container::value_type key_type;
  typedef typename mapped_container::value_type mapped_type;
  typedef typename std::vector<mapped_container>::size_type size_type;

private:
  key_container df_keys;
  std::vector<mapped_container> df_values;
  bool added_first_column;

  // return the names of columns in s separated by delim
  key_container split (const key_type & s, char delim) const;

  // return the index of column key, or df_keys.size () if not found
  size_type look_up (const key_type & key) const;

public:
  explicit DataFrame (const std::string & c_names);
  explicit DataFrame (const key_container & names);

  void print (void) const;

  mapped_container get_column (const key_type & column_name) const;

  mapped_type const & get_element_at (const key_type & column_name,
                                      size_type index) const;
  void set_element_at (const key_type & column_name, size_type index,
                       const mapped_type & value);

  T get_mean (const key_type & column_name) const;

  // add a new column with data
  void set_column (const key_type & column_name,
                   const mapped_container & column_data);

  // return a copy of the DataFrame with rows i such that "c_name[i] == value"
  DataFrame select_equal (const key_type & c_name,
                          const mapped_type & value) const;
};

template <typename T>
DataFrame<T>::DataFrame (const std::string & c_names)
  : DataFrame (split (c_names, ' '))
{}

template <typename T>
DataFrame<T>::DataFrame (const key_container & names)
  : df_keys (names), df_values (df_keys.size ()),
    added_first_column (false)
{}

template <typename T>
typename DataFrame<T>::size_type
DataFrame<T>::look_up (const key_type & key) const
{
  size_type index = 0;
  while (index < df_keys.size () and df_keys[index] != key) ++index;
  return index;
}

template <typename T>
typename DataFrame<T>::mapped_container
DataFrame<T>::get_column (const key_type & column_name) const
{
  const size_type index = look_up (column_name);
  return df_values[index];
}

template <typename T>
T DataFrame<T>::get_mean (const key_type & column_name) const
{
  const size_type index = look_up (column_name);
  mapped_container const & column = df_values[index];
  T sum = T();
  for (const mapped_type & v : column)
    sum += v;
  return sum / column.size ();
}

template <typename T>
void DataFrame<T>::print (void) const
{
  for (size_type i = 0; i < df_keys.size (); ++i)
    {
      std::cout << df_keys[i] << " :: ";

      for (const mapped_type & v : df_values[i])
        std::cout << v << " ";

      std::cout << std::endl;
    }
}

template <typename T>
typename DataFrame<T>::key_container
DataFrame<T>::split (const std::string & s, char delim) const
{
  std::string word;
  key_container keys;
  std::istringstream columns (s);
  while (std::getline (columns, word, delim)) keys.push_back (word);
  return keys;
}

template <typename T>
typename DataFrame<T>::mapped_type const &
DataFrame<T>::get_element_at (const key_type & column_name,
                              size_type index) const
{
  const size_type column_index = look_up (column_name);
  return df_values[column_index][index];
}

template <typename T>
void DataFrame<T>::set_element_at (const key_type & column_name,
                                   size_type index, const mapped_type & value)
{
  const size_type column_index = look_up (column_name);
  df_values[column_index][index] = value;
}

template <typename T>
void DataFrame<T>::set_column (const key_type & column_name,
                               const mapped_container & column_data)
{
  const size_type index = look_up (column_name);

  if (added_first_column)
    {
      mapped_container & column = df_values[index];

      for (size_type i = 0; i < column_data.size (); ++i)
        column[i] = column_data[i];
    }
  else
    {
      added_first_column = true;
      df_values[index] = column_data;

      for (mapped_container & column : df_values)
        column.resize (column_data.size ());
    }
}

template <typename T>
DataFrame<T> DataFrame<T>::select_equal (const key_type & c_name,
                                         const mapped_type & value) const
{
  DataFrame<T> result (df_keys);

  const size_type index = look_up (c_name);
  const mapped_container & column = df_values[index];

  std::vector<size_type> indices;

  // select rows indices satisfying the selection criterion
  for (size_type j = 0; j < column.size (); ++j)
    if (column[j] == value)
      indices.push_back (j);

  for (size_type i = 0; i < df_keys.size (); ++i)
    {
      mapped_container values;
      key_type const & current_name = df_keys[i];
      mapped_container const & current_column = df_values[i];

      for (size_type j : indices)
        values.push_back (current_column[j]);

      result.set_column (current_name, values);
    }

  return result;
}

#endif // DATAFRAME_HH
