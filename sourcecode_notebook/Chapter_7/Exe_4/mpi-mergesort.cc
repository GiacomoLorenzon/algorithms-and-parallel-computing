#include <algorithm>
#include <iostream>
#include <mpi.h>
#include <vector>

int
main (int argc, char *argv[])
{
  MPI_Init (&argc, &argv);

  int rank, size;
  MPI_Comm_rank (MPI_COMM_WORLD, &rank);
  MPI_Comm_size (MPI_COMM_WORLD, &size);

  std::vector<long> numbers;
  if (rank == 0)
    {
      long value;
      while (std::cin >> value) numbers.push_back (value);
    }

  unsigned numbers_count = numbers.size ();
  MPI_Bcast (&numbers_count, 1, MPI_UNSIGNED, 0, MPI_COMM_WORLD);

  unsigned local_share = numbers_count / size;
  unsigned tail = 0;
  if (numbers_count % size > 0)
    {
      ++local_share;
      tail = size - numbers_count % size;
    }
  // Add elements to call the straightforward MPI_Scatter
  if (rank == 0) numbers.resize (local_share * size);

  std::vector<long> local (local_share);
  MPI_Scatter (numbers.data (), local_share, MPI_LONG,
               local.data (), local_share, MPI_LONG,
               0, MPI_COMM_WORLD);

  std::sort (local.begin (),
             // If this process is not the last in the communicator
             size - rank > 1
             ? local.end () : local.end () - tail);

  MPI_Gather (local.data (), local_share, MPI_LONG,
              numbers.data (), local_share, MPI_LONG,
              0, MPI_COMM_WORLD);

  if (rank == 0)
    {
      // Drop the surplus elements added to call MPI_Scatter
      numbers.resize (numbers_count);

      std::vector<long>::iterator middle = numbers.begin () + local_share,
        last = middle + local_share;

      while (last < numbers.end ())
        {
          std::inplace_merge (numbers.begin (), middle, last);
          middle = last;
          last += local_share;
        }

      if (middle < numbers.end ())
        {
          std::inplace_merge (numbers.begin (), middle, numbers.end ());
        }

      for (long value: numbers) std::cout << value << std::endl;
    }

  MPI_Finalize ();
  return 0;
}
