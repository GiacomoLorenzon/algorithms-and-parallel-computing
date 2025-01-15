#ifndef DENSE_MATRIX_HPP
#define DENSE_MATRIX_HPP

#include <istream>
#include <vector>

#include "matrix.hpp"

class DenseMatrix : public Matrix
{
   private:
   std::vector<double> m_data;

   std::size_t sub2ind (std::size_t i, std::size_t j) const;

   public:
   DenseMatrix (std::size_t rows, std::size_t columns,
         double value = 0.0);

   DenseMatrix (std::size_t rows, std::size_t columns,
         const std::vector<double>& values);

   void read (std::istream &);

   void swap (DenseMatrix &);

   double & operator () (std::size_t i, std::size_t j) override;

   double operator () (std::size_t i, std::size_t j) const override;

   DenseMatrix transposed (void) const;

   double * data (void);

   const double * data (void) const;
};

DenseMatrix operator * (const DenseMatrix &, const DenseMatrix &);

void swap (DenseMatrix &, DenseMatrix &);

#endif // DENSE_MATRIX_HH
