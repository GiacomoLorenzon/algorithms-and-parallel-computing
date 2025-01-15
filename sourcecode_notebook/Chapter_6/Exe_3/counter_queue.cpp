#include "counter_queue.hpp"

namespace supermarket
{
  bool
  counter_queue::pick_number (const std::string & customer_id)
  {
    typedef
      std::pair<std::unordered_set<std::string>::iterator, bool>
      insert_return_type;
    const insert_return_type outcome = m_in_line.insert (customer_id);
    const bool added_in_queue = outcome.second;
    if (added_in_queue) m_order.push (customer_id);
    return added_in_queue;
  }

  std::string
  counter_queue::next_customer (void)
  {
    const std::string next = m_order.front ();
    m_order.pop ();
    m_in_line.erase (next);
    return next;
  }

  bool
  counter_queue::empty (void) const
  {
    return m_order.empty ();
  }
}
