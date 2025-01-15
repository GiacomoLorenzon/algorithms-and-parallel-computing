#include "instant_messenger.hh"

namespace im
{
  void messenger::send (key_type timestamp, const mapped_type & message)
  {
    m_data[timestamp] = message;
  }

  std::list<messenger::mapped_type>
  messenger::receive (key_type timestamp) const
  {
    std::list<mapped_type> result;

    for (container_type::const_iterator it = m_data.lower_bound (timestamp);
         it != m_data.cend (); ++it)
      {
        result.push_back (it -> second);
      }

    return result;
  }

  std::list<messenger::mapped_type>
  messenger::search (const std::string & word) const
  {
    std::list<mapped_type> result;

    for (const container_type::value_type & pair : m_data)
      {
        const mapped_type & message = pair.second;

        if (message.find (word) != mapped_type::npos)
          {
            result.push_back (message);
          }
      }

    return result;
  }
}
