#include <iostream>
#include <memory>

#include "ContinousStream.h"
#include "MicroBatch.h"

int main()
{
  auto b1 = std::make_shared<MicroBatch>();// ({1, 2, 3});
  auto b2 = std::make_shared<MicroBatch>();// ({4, 5});
  auto b3 = std::make_shared<MicroBatch>();// ({6, 7});
  b1 -> set_samples ({1, 2, 3});
  b2 -> set_samples ({4, 5});
  b3 -> set_samples ({6, 7});

  ContinousStream stream (2);
  std::cout << "b1: " << b1->get_min() << " "
            << b1->get_max() << " "
            << b1->get_sum() << " " << std::endl;

  stream.add_batch (b1);
  std::cout << "stream: " << stream.get_min() << " "
            << stream.get_max() << " "
            << stream.get_average() << " " << std::endl;

  std::cout << "b2: " << b2->get_min() << " "
            << b2->get_max() << " "
            << b2->get_sum() << " " << std::endl;

  stream.add_batch (b2);
  std::cout << "stream: " << stream.get_min() << " "
            << stream.get_max() << " "
            << stream.get_average() << " " << std::endl;

  stream.add_batch (b3);
  std::cout << "b3: " << b3->get_min() << " "
            << b3->get_max() << " "
            << b3->get_sum() << " " << std::endl;

  std::cout << "stream: " << stream.get_min() << " "
            << stream.get_max() << " "
            << stream.get_average() << " " << std::endl;

  return 0;
}
