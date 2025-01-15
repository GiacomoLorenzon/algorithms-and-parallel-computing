#include <fstream>
#include <iostream>
#include <mpi.h>
#include <sstream>
#include <string>
#include <vector>

#include "MPI_helpers.hh"
#include "word_counter.hh"

int
main (int argc, char * argv[])
{
  constexpr int counts_tag = 1;
  constexpr int words_tag = 2;

  MPI_Init (&argc, &argv);

  const unsigned rank = mpi::rank ();
  const unsigned size = mpi::size ();

  word_counting::word_counter wc;

  {
    std::string basename;
    if (rank == 0) std::cin >> basename;

    unsigned length = basename.size ();
    MPI_Bcast (&length, 1, MPI_UNSIGNED, 0, MPI_COMM_WORLD);

    basename.resize (length);
    MPI_Bcast (&basename[0], length, MPI_CHAR, 0, MPI_COMM_WORLD);

    std::ostringstream filename;
    filename << basename << rank << ".txt";
    std::ifstream input (filename.str ());
    if (input) wc.update_counts (input);
  }

  for (unsigned receiver = 0; receiver < size; ++receiver)
    {
      if (rank != receiver)
        {
          std::ostringstream words_builder;
          std::vector<unsigned> counts;

          const std::pair<char, char> bounds = mpi::get_processor_bounds (receiver);
          const std::string low {bounds.first}, up {bounds.second};
          typedef word_counting::word_counter::const_iterator const_iterator;
          const const_iterator end = wc.upper_bound (up);
            
          for (const_iterator it = wc.lower_bound (low);
               it != end; ++it)
            {
              words_builder << it->first << std::endl;
              counts.push_back (it->second);
            }

          const std::string words = words_builder.str ();
          const unsigned words_length = words.size ();
          MPI_Send (&words_length, 1, MPI_UNSIGNED, receiver,
                    words_tag, MPI_COMM_WORLD);
          MPI_Send (&words[0], words_length, MPI_CHAR,
                    receiver, words_tag, MPI_COMM_WORLD);

          const unsigned num_counts = counts.size ();
          MPI_Send (&num_counts, 1, MPI_UNSIGNED, receiver,
                    counts_tag, MPI_COMM_WORLD);
          MPI_Send (counts.data (), num_counts, MPI_UNSIGNED,
                    receiver, counts_tag, MPI_COMM_WORLD);
        }
      else
        {
          for (unsigned sender = 0; sender < size; ++sender)
            {
              if (rank != sender)
                {
                  unsigned length {0};

                  MPI_Recv (&length, 1, MPI_UNSIGNED, sender, words_tag,
                            MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                  std::string words (length, '?');
                  MPI_Recv (&words[0], length, MPI_CHAR, sender,
                            words_tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

                  MPI_Recv (&length, 1, MPI_UNSIGNED, sender, counts_tag,
                            MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                  std::vector<unsigned> counts (length);
                  MPI_Recv (counts.data (), length, MPI_UNSIGNED, sender,
                            counts_tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

                  std::istringstream words_stream (words);
                  for (unsigned count: counts)
                    {
                      std::string word;
                      words_stream >> word;
                      wc.update_word (word, count);
                    }
                }
            }
        }
    }

  const std::pair<char, char> bounds = mpi::get_processor_bounds (rank);
  wc.keep_between (bounds.first, bounds.second);

  for (word_counting::word_counter::value_type const& pair: wc)
    {
      std::ostringstream builder;
      builder << pair.first << ": " << pair.second << "\n";
      std::cout << builder.str ();
    }

  MPI_Finalize ();
  return 0;
}
