// main.cc
#include <mpi.h>

#include "grep.hh"

int main (int argc, char * argv[])
{
  MPI_Init (&argc, &argv);
  grep::lines_found local_filtered_lines;
  unsigned local_lines_number;
  grep::search_string (argv[1], argv[2], local_filtered_lines, local_lines_number);
  grep::print_result (local_filtered_lines, local_lines_number);
  MPI_Finalize();
  return 0;
}
