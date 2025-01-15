#ifndef __STANDARD_SCALER_HEADER__
#define __STANDARD_SCALER_HEADER__

#include "Scaler.hpp"
#include <vector>

class StandardScaler : public Scaler
{
  std::vector<double> means;
  std::vector<double> sigmas;

public:

  StandardScaler(const matrix & m_, unsigned r_, unsigned c_) : Scaler(m_, r_, c_) {};

  void fit(void) override;
  void fit_transform(void) override;
  void inverse_transform(void) override;
};

#endif
