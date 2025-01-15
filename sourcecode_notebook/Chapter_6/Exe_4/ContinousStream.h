#ifndef CONTINOUSSTREAM_H
#define CONTINOUSSTREAM_H

#include <memory>
#include <vector>

#include "MicroBatch.h"

class ContinousStream
{
  std::vector< std::shared_ptr<const MicroBatch> > batches;

  std::vector<double> mins;
  std::vector<double> maxs;
  std::vector<double> sums;

  size_t next_batch = 0;

  unsigned window_size;

public:
  ContinousStream (unsigned time_window)
    : window_size (time_window) {}

  double get_min() const;
  double get_max() const;
  double get_average() const;

  void add_batch (std::shared_ptr<const MicroBatch> b);
};

#endif // CONTINOUSSTREAM_H
