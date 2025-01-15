#ifndef __SCALER_HEADER__
#define __SCALER_HEADER__

#include <vector>

class Scaler
{
public:
  typedef std::vector<std::vector<double>> matrix;

private:
  matrix m;
  unsigned r;
  unsigned c;

public:

  Scaler(const matrix & m_, unsigned r_, unsigned c_) : m(m_), r(r_), c(c_) {};

  virtual void fit(void) = 0;
  virtual void fit_transform(void) = 0;
  virtual void inverse_transform(void) = 0;
};

#endif
