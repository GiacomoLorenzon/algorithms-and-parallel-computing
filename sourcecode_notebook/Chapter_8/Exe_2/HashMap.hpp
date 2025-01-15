#ifndef HASHMAP_HH
#define HASHMAP_HH

#include <list>
#include <iostream>
#include <vector>
#include <utility>

template <typename K, typename T>
class HashMap {

  typedef std::vector<std::list<std::pair<K, T>>> table;

  double max_load_factor; //max_load_factor
  size_t bucket_count = 0; //vector length
  size_t count = 0; //total inserted elements

  std::hash<K> hash_code;

  void
  resize (void);

  table hashtable;

public:

  HashMap():
      max_load_factor(0.75), bucket_count(8),
      count(0), hashtable(bucket_count) {}

  void
  add (const K & key, const T & value);

  void
  remove (const K & key);

  void
  dump_internal_structure() const;

};   /* end of class declaration */

template <typename K, typename T>
void
HashMap<K, T>::resize (void)
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

template <typename K, typename T>
void
HashMap<K, T>::add (const K & key, const T & value)
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

template <typename K, typename T>
void
HashMap<K, T>::remove (const K & key)
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

template <typename K, typename T>
void
HashMap<K, T>::dump_internal_structure() const
{
   for(std::size_t bucket_index = 0; bucket_index < hashtable.size(); bucket_index++)
   {
      std::cerr << "Bucket " << bucket_index << ": " << std::endl;
      for(const auto collision : hashtable[bucket_index])
      {
         std::cerr << "   (" << collision.first << ", " << collision.second << ")" << std::endl;
      }
      std::cerr << std::endl;
   }
}


#endif /* HASHMAP_HH */
