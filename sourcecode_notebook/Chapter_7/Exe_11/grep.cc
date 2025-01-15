// grep.cc
#include <fstream>
#include <iostream>
#include <sstream>

#include <mpi.h>

#include "grep.hh"

namespace grep
{
  void search_string (const std::string & file_name,
                      const std::string & search_string,
                      lines_found & local_filtered_lines,
                      unsigned & local_lines_number)
  {
    int rank (0);
    MPI_Comm_rank (MPI_COMM_WORLD, &rank);
    const unsigned rk (rank);
    local_lines_number = 0;
    std::ostringstream file_name_builder;
    file_name_builder << file_name << '-' << rk;
    const std::string local_file_name = file_name_builder.str ();
    std::ifstream f_stream (local_file_name);

    // read input file line by line
    for (std::string line; std::getline (f_stream, line); )
      {
        //increment local number of lines
        ++local_lines_number;

        if (line.find (search_string) != std::string::npos)
          {
            local_filtered_lines.push_back ({local_lines_number, line});
          }
      }
  }

  void print_result (const lines_found & local_filtered_lines,
                     unsigned local_lines_number)
  {
    int rank (0), size (0);
    MPI_Comm_rank (MPI_COMM_WORLD, &rank);
    MPI_Comm_size (MPI_COMM_WORLD, &size);
    const unsigned rk (rank);
    const unsigned sz (size);

    if (rk == 0)
      {
        lines_found global_filtered_lines (local_filtered_lines);

        // append to global_filtered_lines the lines found by other processes
        for (unsigned remote_process = 1; remote_process < sz; ++remote_process)
          {
            unsigned remote_lines;
            // receive the number of lines in the local file
            MPI_Recv (&remote_lines, 1, MPI_UNSIGNED, remote_process, 0,
                      MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            // receive the number of lines to be received
            unsigned filtered_lines;
            MPI_Recv (&filtered_lines, 1, MPI_UNSIGNED,
                      remote_process, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            // receive lines
            for (unsigned i = 0; i < filtered_lines; ++i)
              {
                unsigned current_line_number;
                MPI_Recv (&current_line_number, 1, MPI_UNSIGNED,
                          remote_process, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                unsigned length = 0;
                MPI_Recv (&length, 1, MPI_UNSIGNED,
                          remote_process, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                std::string new_line (length, '\0');
                MPI_Recv (&new_line[0], length, MPI_CHAR,
                          remote_process, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                // add new line and compute offset
                global_filtered_lines.push_back (std::make_pair (local_lines_number +
                                        current_line_number, new_line));
              }

            local_lines_number += remote_lines;
          }

        // print all filtered lines
        for (const number_and_line & n_l : global_filtered_lines)
          {
            std::cout << n_l.first << ": " << n_l.second << std::endl;
          }
      }
    else
      {
        // send to rank 0 the number of lines of the local file
        // in a way the line number can be updated
        MPI_Send (&local_lines_number, 1, MPI_UNSIGNED, 0, 0, MPI_COMM_WORLD);
        // send to rank 0 the number of filtered lines
        const unsigned filtered_lines = local_filtered_lines.size();
        MPI_Send (&filtered_lines, 1, MPI_UNSIGNED, 0, 0, MPI_COMM_WORLD);

        // send lines
        for (const number_and_line & n_l : local_filtered_lines)
          {
            // send line number
            MPI_Send (&n_l.first, 1, MPI_UNSIGNED, 0, 0, MPI_COMM_WORLD);
            const unsigned length = n_l.second.size();
            // send string length
            MPI_Send (&length, 1, MPI_UNSIGNED, 0, 0, MPI_COMM_WORLD);
            // send string
            MPI_Send (&(n_l.second)[0], length, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
          }
      }
  }
}
