#include "matrix.hpp"

Matrix::Matrix (std::size_t rows, std::size_t cols):
    n_rows (rows), n_cols (cols) {}

std::size_t
Matrix::get_n_cols() const
{
    return n_cols;
}

std::size_t
Matrix::get_n_rows() const
{
    return n_rows;
}

