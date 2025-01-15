#include <iostream>
#include <list>
#include <string>
#include <vector>

#include "engine.hh"
#include "knowledge_base.hh"

int
main (void)
{
  // create the knowledge base
  const search_engine::knowledge_base kb = search_engine::create_default_kb ();
  // create the search engine and initialize it to work on the knowledge base
  const search_engine::engine libero (kb);

  std::list<std::string> searched_sentence;
  std::string word;
  // read keywords to be serched in the KB
  while (std::cin >> word) searched_sentence.push_back (word);

  std::vector<std::string> links =
    libero.search (searched_sentence.cbegin (), searched_sentence.cend ());

  for (const std::string & url: links)
  {
    std::cout << url << std::endl;
  }

  return 0;
}
