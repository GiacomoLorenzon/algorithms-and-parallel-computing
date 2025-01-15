#include "DataFrame.hpp"

DataFrame::DataFrame (const key_type & c_names)
  : DataFrame (split (c_names, ' '))
{}

DataFrame::DataFrame (const key_container & names)
  : df_keys (names), df_values (df_keys.size ()),
    added_first_column (false)
{}

DataFrame::key_container
DataFrame::split (const key_type & s, char delim) const
{
  key_type word;
  key_container keys;
  std::istringstream columns (s);
  while (std::getline (columns, word, delim)) 
    keys.push_back (word);
  return keys;
}

DataFrame::size_type
DataFrame::look_up (const key_type & key) const
{
  size_type index = 0;
  while (index < df_keys.size () and df_keys[index] != key) 
    ++index;
  return index;
}

const DataFrame::mapped_type &
DataFrame::get_column (const key_type & column_name) const
{
  const size_type index = look_up (column_name);
  return df_values[index];
}

double
DataFrame::get_element_at (const key_type & column_name,
                            size_type index) const
{
  const size_type column_index = look_up (column_name);
  return df_values[column_index][index];
}

void
DataFrame::set_element_at (const key_type & column_name, size_type index, 
                           double value)
{
  const size_type column_index = look_up (column_name);
  df_values[column_index][index] = value;
}

double
DataFrame::get_mean (const key_type & column_name) const
{
  const size_type index = look_up (column_name);
  const mapped_type & column = df_values[index];
  double sum = 0.;
  for (double v : column)
    sum += v;
  return sum / column.size ();
}

void
DataFrame::set_column (const key_type & column_name,
                        const mapped_type & column_data)
{
  const size_type index = look_up (column_name);

  if (added_first_column)
    {
      mapped_type & column = df_values[index];

      for (size_type i = 0; i < column_data.size (); ++i)
        column[i] = column_data[i];
    }
  else
    {
      added_first_column = true;
      df_values[index] = column_data;

      for (mapped_type & column : df_values)
        column.resize (column_data.size ());
    }
}

DataFrame 
DataFrame::select_equal (const key_type & c_name,
                          double value) const
{
  DataFrame result (df_keys);

  const size_type index = look_up (c_name);
  const mapped_type & column = df_values[index];

  std::vector<size_type> indices;

  // select rows indices satisfying the selection criterion
  for (size_type j = 0; j < column.size (); ++j)
    if (column[j] == value)
      indices.push_back (j);

  for (size_type i = 0; i < df_keys.size (); ++i)
    {
      mapped_type values;
      const key_type & current_name = df_keys[i];
      const mapped_type & current_column = df_values[i];

      for (size_type j : indices)
        values.push_back (current_column[j]);

      result.set_column (current_name, values);
    }

  return result;
}

void
DataFrame::print (void) const
{
  for (size_type i = 0; i < df_keys.size (); ++i)
    {
      std::cout << df_keys[i] << " :: ";

      for (double v : df_values[i])
        std::cout << v << " ";

      std::cout << std::endl;
    }
}
