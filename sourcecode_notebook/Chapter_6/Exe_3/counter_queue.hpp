#ifndef _COUNTER_QUEUE_
#define _COUNTER_QUEUE_

#include <queue>
#include <string>
#include <unordered_set>

namespace supermarket
{
  class counter_queue
  {
    std::queue<std::string> m_order;
    std::unordered_set<std::string> m_in_line;

  public:
    bool
    pick_number (const std::string & customer_id);

    std::string
    next_customer (void);

    bool
    empty (void) const;
  };
}

#endif // _COUNTER_QUEUE_
