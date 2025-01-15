#include "matrix.hpp"

Matrix::Matrix (std::size_t rows, std::size_t cols)
  : n_rows (rows), n_cols (cols) {}

std::size_t Matrix::get_n_cols (void) const
{
  return n_cols;
}

std::size_t Matrix::get_n_rows (void) const
{
  return n_rows;
}
