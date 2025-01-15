#ifndef __MIN_MAX_SCALER_HEADER__
#define __MIN_MAX_SCALER_HEADER__

#include "Scaler.hpp"
#include <vector>

class MinMaxScaler : public Scaler
{
  std::vector<double> mins;
  std::vector<double> maxs;
  double min;
  double max;

public:

  MinMaxScaler(const matrix & m_, unsigned r_, unsigned c_, double min_, double max_)
    : Scaler(m_, r_, c_), min(min_), max(max_) {};

  void fit(void) override;
  void fit_transform(void) override;
  void inverse_transform(void) override;
};

#endif
