#ifndef MICROBATCH_H
#define MICROBATCH_H

#include <vector>

class MicroBatch
{
  std::vector<double> samples;

public:
  MicroBatch (const std::vector<double> & v)
    : samples (v) {}

  MicroBatch() {}

  double get_min() const;
  double get_max() const;
  double get_sum() const;

  unsigned get_n_samples() const;

  void set_samples (const std::vector<double> & v);
};

#endif // MICROBATCH_H
