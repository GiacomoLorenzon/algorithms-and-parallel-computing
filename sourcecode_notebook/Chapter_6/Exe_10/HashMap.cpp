#include "HashMap.hpp"

void
HashMap::resize (void)
{
  bucket_count *= 2;

  table temp (bucket_count);
  hashtable.swap (temp);

  count = 0;

  // iterate over old hash table and add each entry to a new table.
  for (const auto & bucket: temp)
    {
      for (const auto & couple: bucket)
        {
          add (couple.first, couple.second);
        }
    }
}

void
HashMap::add (const key_type & key, const value_type & value)
{
  const std::size_t idx = hash_code (key) % bucket_count;

  // look if the key is already inserted
  auto it = hashtable[idx].cbegin ();
  while (it != hashtable[idx].cend () and it->first != key)
    ++it;

  // if you reach the end, you could not find the pair
  if (it == hashtable[idx].cend ())
    {
      hashtable[idx].push_back ({key, value});
      ++count;
    }

  if (static_cast<double>(count) / bucket_count > max_load_factor)
    resize();
}

void
HashMap::remove (const key_type & key)
{
  const std::size_t idx = hash_code (key) % bucket_count;

  auto it = hashtable[idx].cbegin ();
  while (it != hashtable[idx].cend () and it->first != key)
    ++it;

  if (it != hashtable[idx].cend ())
    {
      hashtable[idx].erase (it);
      --count;
    }
}

void
HashMap::dump_internal_structure() const
{
   for(std::size_t bucket_index = 0; 
       bucket_index < hashtable.size(); bucket_index++)
   {
      std::cerr << "Bucket " << bucket_index << ": " << std::endl;
      for(const auto & collision : hashtable[bucket_index])
      {
         std::cerr << "   (" << collision.first << ", " 
                   << collision.second << ")" << std::endl;
      }
      std::cerr << std::endl;
   }
}