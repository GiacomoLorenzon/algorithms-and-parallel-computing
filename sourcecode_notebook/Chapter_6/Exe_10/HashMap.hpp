#ifndef HASHMAP_HH
#define HASHMAP_HH

#include <list>
#include <iostream>
#include <vector>
#include <utility>

class HashMap {
  
  typedef int key_type;
  typedef int value_type;

  typedef std::vector<std::list<std::pair<key_type, value_type>>> table;

  double max_load_factor; //max_load_factor
  size_t bucket_count = 0; //vector length
  size_t count = 0; //total inserted elements

  std::hash<key_type> hash_code;

  void
  resize (void);

  table hashtable;

public:

  HashMap():
      max_load_factor(0.75), bucket_count(8),
      count(0), hashtable(bucket_count) {}

  void
  add (const key_type & key, const value_type & value);

  void
  remove (const key_type & key);

  void
  dump_internal_structure() const;

};   /* end of class declaration */

#endif /* HASHMAP_HH */
