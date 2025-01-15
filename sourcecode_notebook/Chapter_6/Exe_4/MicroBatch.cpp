#include <algorithm>
#include <numeric>

#include "MicroBatch.h"


double MicroBatch::get_min() const
{
  return * std::min_element (samples.cbegin(), samples.cend());
}

double MicroBatch::get_max() const
{
  return * std::max_element (samples.cbegin(), samples.cend());
}

double MicroBatch::get_sum() const
{
  return std::accumulate (samples.cbegin(), samples.cend(), 0.);
}

unsigned MicroBatch::get_n_samples() const
{
  return samples.size();
}

void MicroBatch::set_samples (const std::vector<double> & v)
{
  samples = v;
}
