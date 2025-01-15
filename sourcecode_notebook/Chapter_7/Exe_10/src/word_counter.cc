#include <algorithm>
#include <cctype>
#include <iterator>

#include "word_counter.hh"

namespace word_counting
{
  word_counter::key_type
  word_counter::parse_key (key_type const& word)
  {
    key_type key;
    std::remove_copy_if (word.cbegin (), word.cend (),
                         std::back_inserter (key), ispunct);
    std::transform (key.begin (), key.end (),
                    key.begin (), tolower);
    return key;
  }

  void
  word_counter::update_counts (std::istream & input)
  {
    key_type word;
    while (input >> word) update_word (word, 1);
  }

  void
  word_counter::update_word (key_type const& word, mapped_type count)
  {
    const key_type key = parse_key (word);
    if (not key.empty ())
      {
        count_container::iterator match = counts.find (key);
        if (match != counts.end ()) match -> second += count;
        else counts[key] = count;
      }
  }

  void
  word_counter::keep_between (char begin, char end)
  {
    const std::string b {begin}, e {end};
    const const_iterator first = lower_bound (b),
      last = upper_bound (e);
    counts.erase (counts.cbegin (), first);
    counts.erase (last, counts.cend ());
  }

  word_counter::const_iterator
  word_counter::lower_bound (key_type const& k) const
  {
    return counts.lower_bound (k);
  }

  word_counter::const_iterator
  word_counter::upper_bound (key_type const& k) const
  {
    return counts.upper_bound (k);
  }

  word_counter::const_iterator
  word_counter::cbegin (void) const
  {
    return counts.cbegin ();
  }

  word_counter::const_iterator
  word_counter::cend (void) const
  {
    return counts.cend ();
  }

  word_counter::const_iterator
  word_counter::begin (void) const
  {
    return cbegin ();
  }

  word_counter::const_iterator
  word_counter::end (void) const
  {
    return cend ();
  }
}
