#ifndef __INSTANT_MESSENGER__
#define __INSTANT_MESSENGER__

#include <list>
#include <map>
#include <string>

namespace im
{
  class messenger
  {
    typedef std::map<unsigned long, std::string> container_type;

    container_type m_data;

  public:
    typedef container_type::key_type key_type;
    typedef container_type::mapped_type mapped_type;
    typedef container_type::value_type value_type;

    void send (key_type, const mapped_type &);
    std::list<mapped_type> receive (key_type) const;
    std::list<mapped_type> search (const std::string &) const;
  };
}

#endif // __INSTANT_MESSENGER__
