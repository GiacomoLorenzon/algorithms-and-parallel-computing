#include "ContinousStream.h"

#include <iostream>

double ContinousStream::get_min() const
{
  return * std::min_element (mins.cbegin(), mins.cend());
}

double ContinousStream::get_max() const
{
  return * std::max_element (maxs.cbegin(), maxs.cend());
}

double ContinousStream::get_average() const
{
  double sum = 0.;
  unsigned n_samples = 0;

  for (size_t i = 0; i < sums.size(); ++i)
    {
      sum += sums[i];
      n_samples += batches[i]->get_n_samples();
    }

  return sum / n_samples;
}

void ContinousStream::add_batch (std::shared_ptr<const MicroBatch> b)
{
  // still creating the window
  if (batches.size() < window_size)
    {
      batches.push_back (b);

      sums.push_back (b->get_sum());
      mins.push_back (b->get_min());
      maxs.push_back (b->get_max());

      next_batch = (next_batch + 1) % window_size;
    }
  else // replace one existing batch
    {    
      batches[next_batch] = b;

      sums[next_batch] = b->get_sum();
      mins[next_batch] = b->get_min();
      maxs[next_batch] = b->get_max();
      
      next_batch = (next_batch + 1) % window_size;
    }
}
