#ifndef __WORD_COUNTER_HH__
#define __WORD_COUNTER_HH__

#include <istream>
#include <map>
#include <string>

namespace word_counting
{
  class word_counter
  {
  private:
    typedef std::map<std::string, unsigned> count_container;

  public:
    typedef count_container::key_type key_type;
    typedef count_container::mapped_type mapped_type;
    typedef count_container::value_type value_type;
    typedef count_container::const_iterator const_iterator;

  private:
    count_container counts;

    key_type parse_key (key_type const&);

  public:
    void update_counts (std::istream &);
    
    void update_word (key_type const&, mapped_type);

    void keep_between (char begin, char end);

    const_iterator lower_bound (key_type const&) const;
    
    const_iterator upper_bound (key_type const&) const;

    const_iterator cbegin (void) const;
    
    const_iterator cend (void) const;
    
    const_iterator begin (void) const;
    
    const_iterator end (void) const;
  };
}

#endif // __WORD_COUNTER_HH__
