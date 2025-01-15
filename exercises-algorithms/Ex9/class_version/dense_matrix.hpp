#ifndef DENSE_MATRIX_HPP
#define DENSE_MATRIX_HPP

#include <istream>
#include <vector>

#include "matrix.hpp"

class DenseMatrix : public Matrix
{
   private:
       std::vector<double> m_data;

       /*
        * [1 2 3
        *  4 5 6]
        *
        * [1 2 3 4 5 6]
        *
        * A(1,0) --> m_data[3]
        *
        * */

       std::size_t sub2ind (std::size_t i, std::size_t j) const;

   public:
       DenseMatrix (std::size_t rows, std::size_t columns,
             double value = 0.0);

       DenseMatrix (std::size_t rows, std::size_t columns,
             const std::vector<double> & values);

       void read (std::istream &);

       void swap (DenseMatrix &);   // A.swap(B)

       double & operator () (std::size_t i, std::size_t j) override;

       double operator () (std::size_t i, std::size_t j) const override;

       DenseMatrix transposed (void) const;

       double * data (void);        // A.data()

       const double * data (void) const;

        virtual ~DenseMatrix() = default;
};

DenseMatrix operator * (const DenseMatrix &, const DenseMatrix &);

void swap (DenseMatrix &, DenseMatrix &);

#endif // DENSE_MATRIX_HH
