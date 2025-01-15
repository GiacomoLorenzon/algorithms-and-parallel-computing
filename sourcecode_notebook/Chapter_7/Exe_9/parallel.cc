#include <algorithm>
#include <cstring>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

#include <mpi.h>

#include "engine.hh"
#include "knowledge_base.hh"

int
main (int argc, char * argv[])
{
  MPI_Init (&argc, &argv);

  int rank, size;
  MPI_Comm_rank (MPI_COMM_WORLD, &rank);
  MPI_Comm_size (MPI_COMM_WORLD, &size);

  std::vector<std::string> searched_sentence;

  // read keywords from master
  if (rank == 0)
  {
    std::string word;
    while (std::cin >> word) searched_sentence.push_back (word);
  }

  unsigned word_count = searched_sentence.size ();
  MPI_Bcast (&word_count, 1, MPI_UNSIGNED, 0, MPI_COMM_WORLD);

  // compute how many words every process will take care of
  unsigned local_share = word_count / size;
  if (rank < word_count % size) ++local_share;
  std::vector<std::string> my_part (local_share);

  if (rank == 0)
  {
    for (std::size_t i = 0; i < searched_sentence.size (); ++i)
    {
      const std::size_t dest = i % size;

      if (dest > 0)
      {
        std::string send_buffer = searched_sentence[i];
        unsigned buffer_size = send_buffer.size();
        MPI_Send (&buffer_size, 1, MPI_UNSIGNED, dest, 0, 
                            MPI_COMM_WORLD);
        MPI_Send (&send_buffer[0], buffer_size, MPI_CHAR,
                  dest, 1, MPI_COMM_WORLD);
      }
      else
      {
        my_part[i/size] = searched_sentence[i];
      }
    }
  }
  else
  {
    for (unsigned i = 0; i < local_share; ++i)
    {
      MPI_Status status;
      unsigned buffer_size;
      MPI_Recv (&buffer_size, 1, MPI_UNSIGNED, 0, 0, 
                          MPI_COMM_WORLD, &status);
      std::string recv_buffer(buffer_size,'\0');
      MPI_Recv (&recv_buffer[0], buffer_size, MPI_CHAR,
                0, 1, MPI_COMM_WORLD, &status);
      my_part[i] = recv_buffer;
    }
  }

  // create the knowledge base
  const search_engine::knowledge_base kb = search_engine::create_default_kb ();
  // create the search engine and initialize it to work on the knowledge base
  const search_engine::engine libero (kb);
  // do partial search with the engine
  std::vector<std::string> my_urls =
    libero.search (my_part.cbegin (), my_part.cend ());

  std::sort (my_part.begin (), my_part.end ());

  /* everyone sends its partial search result, while master
   * both collects and intersects them
   */
  if (rank == 0)
  {
    for (int r = 1; r < size; ++r)
    {
      unsigned its_url_count = 0;
      MPI_Status status;
      MPI_Recv (&its_url_count, 1, MPI_UNSIGNED,
                r, 2, MPI_COMM_WORLD, &status);

      std::vector<std::string> its_urls (its_url_count);

      for (std::string & url: its_urls)
      {
        unsigned buffer_size;
        MPI_Recv (&buffer_size, 1, MPI_UNSIGNED, r, 3, 
                            MPI_COMM_WORLD, &status);
        std::string recv_buffer(buffer_size,'\0');
        MPI_Recv (&recv_buffer[0], buffer_size, MPI_CHAR,
                  r, 4, MPI_COMM_WORLD, &status);
        url = recv_buffer;
      }

      std::vector<std::string> tmp;
      tmp.resize (std::min (my_urls.size (), its_urls.size ()));

      auto it = std::set_intersection (my_urls.cbegin (),
                                              my_urls.cend (),
                                              its_urls.cbegin (),
                                              its_urls.cend (),
                                              tmp.begin());
      tmp.resize (it - tmp.begin());

      my_urls.swap (tmp);
    }
  }
  else
    {
      const unsigned url_count = my_urls.size ();
      MPI_Send (&url_count, 1, MPI_UNSIGNED, 0, 2, MPI_COMM_WORLD);

      for (const std::string & url: my_urls)
        {
          unsigned buffer_size = url.size();
          MPI_Send (&buffer_size, 1, MPI_UNSIGNED, 0, 3, MPI_COMM_WORLD);
          MPI_Send (&url[0], buffer_size, MPI_CHAR,
                    0, 4, MPI_COMM_WORLD);
        }
    }

  // output from master
  if (rank == 0)
    {
      for (const std::string & url: my_urls)
        {
          std::cout << url << std::endl;
        }
    }

  MPI_Finalize ();
  return 0;
}
