#include <sstream>
#include <string>
#include <iostream>

#include "dense_matrix.hpp"

DenseMatrix::DenseMatrix (std::size_t rows, std::size_t columns, double value) :
   Matrix(rows, columns),
   m_data (n_rows * n_cols, value)
{
}

DenseMatrix::DenseMatrix(std::size_t rows, std::size_t columns, const std::vector<double> & values) :
   Matrix(rows, columns),
   m_data(values)
{}

std::size_t
DenseMatrix::sub2ind (std::size_t i, std::size_t j) const
{
   return i * n_cols + j;
}

   void
DenseMatrix::read (std::istream & in)
{
   std::string line;
   std::getline (in, line);

   std::istringstream first_line (line);
   first_line >> n_rows >> n_cols;
   m_data.resize (n_rows * n_cols);

   for (std::size_t i = 0; i < n_rows; ++i)
   {
      std::getline (in, line);
      std::istringstream current_line (line);

      for (std::size_t j = 0; j < n_cols; ++j)
      {
         /* alternative syntax: current_line >> operator () (i, j);
          * or: current_line >> m_data[sub2ind (i, j)];
          */
         current_line >> (*this)(i, j);
      }
   }
}

   void
DenseMatrix::swap (DenseMatrix & rhs)
{
   using std::swap;
   swap (n_rows, rhs.n_rows);
   swap (n_cols, rhs.n_cols);
   swap (m_data, rhs.m_data);
}

DenseMatrix
DenseMatrix::transposed (void) const
{
   DenseMatrix At (n_cols, n_rows);

   for (std::size_t i = 0; i < n_cols; ++i)
      for (std::size_t j = 0; j < n_rows; ++j)
         At(i, j) = operator () (j, i);

   return At;
}

   double *
DenseMatrix::data (void)
{
   return m_data.data ();
}

const double *
DenseMatrix::data (void) const
{
   return m_data.data ();
}

   DenseMatrix
operator * (const DenseMatrix & A, const DenseMatrix & B)
{
   DenseMatrix C (A.get_n_rows(), B.get_n_cols());

   for (std::size_t i = 0; i < A.get_n_rows(); ++i)
      for (std::size_t j = 0; j < B.get_n_cols(); ++j)
         for (std::size_t k = 0; k < A.get_n_cols(); ++k)
            C(i, j) += A(i, k) * B(k, j);

   return C;
}

   void
swap (DenseMatrix & A, DenseMatrix & B)
{
   A.swap (B);
}

double & DenseMatrix::operator()(std::size_t i, std::size_t j)
{
   return m_data.at(sub2ind(i, j));
}

double DenseMatrix::operator()(std::size_t i, std::size_t j) const
{
   return m_data.at(sub2ind(i, j));
}
