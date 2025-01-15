#include "DataFrame.h"

DataFrame::DataFrame (const key_type & c_names)
  : DataFrame ()
{
  std::vector<key_type> columns_names = split (c_names, ' ');

  for (const key_type & name : columns_names)
    df_data[name];
}

DataFrame::DataFrame (void)
  : added_first_column (false), n_rows (0) 
{}

std::vector<DataFrame::key_type>
DataFrame::split (const key_type & s,  char delim) const
{
  key_type word;
  std::vector<key_type> v;
  std::istringstream columns (s);

  while (std::getline (columns, word, delim)) v.push_back (word);

  return v;
}

bool
DataFrame::check_column_name (const key_type & column_name) const
{
  return df_data.find (column_name) != df_data.end();
}

void
DataFrame::set_column_data (const key_type & column_name,
                            const mapped_type & column_data)
{
  if (! added_first_column)
    {
      n_rows = column_data.size();
      added_first_column = true;
      for (df_type::iterator it = df_data.begin(); it != df_data.end(); it++)
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

DataFrame::mapped_type
DataFrame::get_column (const key_type & column_name) const
{
  if (check_column_name (column_name))
    return df_data.at (column_name);
  else
    {
      std::cerr << "Error, " << column_name << " is unknown" << std::endl;
      return std::vector<double> ();
    }
}

double
DataFrame::get_element_at (const key_type & column_name,
                           size_type index) const
{
  if (check_column_name (column_name))
    if (index < n_rows)
      return df_data.at (column_name)[index];
    else
      {
        std::cerr << "Error, index out of bound" << std::endl;
        return std::numeric_limits<double>::quiet_NaN();
      }
  else
    {
      std::cerr << "Error, " << column_name << " is unknown" << std::endl;
      return std::numeric_limits<double>::quiet_NaN();
    }
}

void
DataFrame::set_element_at (const key_type & column_name,
                            size_type index, double value)
{
  if (check_column_name (column_name))
    if (index < n_rows)
      df_data[column_name][index] = value;
    else
      std::cerr << "Error, index out of bound" << std::endl;
  else
    std::cerr << "Error, " << column_name << " is unknown" << std::endl;
}

double
DataFrame::get_mean (const key_type & column_name) const
{
  if (check_column_name (column_name))
    {
      double sum = 0.;

      for (double d : df_data.at (column_name))
        sum += d;

      return sum / n_rows;
    }
  else
    {
      std::cerr << "Error, " << column_name << " is unknown" << std::endl;
      return std::numeric_limits<double>::quiet_NaN();
    }
}

void
DataFrame::set_column (const key_type & column_name,
                        const mapped_type & column_data)
{
  if (check_column_name (column_name))
    set_column_data (column_name, column_data);
  else
    std::cerr << "Error, " << column_name << " is unknown" << std::endl;
}

void
DataFrame::add_column (const key_type & column_name,
                        const mapped_type & column_data)
{
  if (! check_column_name (column_name))
    set_column_data (column_name, column_data);
  else
    std::cerr << "Error, " << column_name
              << " is already included in the DataFrame"
              << std::endl;
}

DataFrame
DataFrame::select_equal (const key_type & c_name,
                          double value) const
{
  if (! check_column_name (c_name))
    {
      std::cerr << "Error, " << c_name << " is unknown" << std::endl;
      return DataFrame();
    }

  std::vector<size_type> indexes; // solution indexes
  const mapped_type & relevant_column = df_data.at (c_name);

  // select rows indexes satisfying the selection criterion
  for (size_type i = 0; i < n_rows; ++i)
    if (relevant_column[i] == value)
      indexes.push_back (i);

  DataFrame result;

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

void
DataFrame::print (void) const
{
  for (const value_type & element : df_data)
    {
      std::cout << element.first << " :: ";

      for (const double & d : element.second)
        std::cout << d << " ";

      std::cout << std::endl;
    }
}
