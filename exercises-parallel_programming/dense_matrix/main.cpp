#include <iostream>
#include <cmath>
#include <string>
#include <sstream>

#include "dense_matrix.h"

double frobenius_norm (const std::string & file_name);

int main (int argc, char *argv[])
{
    MPI_Init (&argc, &argv);

    int rank (0), size (0);

    MPI_Comm_rank (MPI_COMM_WORLD, &rank);
    MPI_Comm_size (MPI_COMM_WORLD, &size);

    std::string file_name = "pluto";

    double norm = frobenius_norm(file_name);

    if (rank == 0)
        std::cout << norm << std::endl;
    MPI_Finalize ();
    return 0;
}

double frobenius_norm (const std::string & file_name)
{
    int rank, size;

    MPI_Comm_rank (MPI_COMM_WORLD, &rank);
    MPI_Comm_size (MPI_COMM_WORLD, &size);

    la::dense_matrix A;
    int r,c;

    if ( rank == 0 )
    {
        std::ifstream ifs {file_name};
        A.read(ifs);

        r = A.rows();
        c = A.columns();
    }

    MPI_Bcast ( &r, 1, MPI_UNSIGNED, 0, MPI_COMM_WORLD );
    MPI_Bcast ( &c, 1, MPI_UNSIGNED, 0, MPI_COMM_WORLD );

    la::dense_matrix local_matrix( r / size, c );

    MPI_Scatter ( A.data(), c * r / size, MPI_DOUBLE,
                  local_matrix.data(), c * r / size, MPI_DOUBLE,
                  0, MPI_COMM_WORLD);

    double local_sum = 0;

    for ( unsigned i = 0; i < r/size; i++ )
        for ( unsigned j = 0; j < c; j++ )
            local_sum += local_matrix(i,j) * local_matrix(i,j);

    double sum = 0;

    MPI_Allreduce ( &local_sum, &sum, 1, MPI_DOUBLE,
                    MPI_SUM, MPI_COMM_WORLD);

    sum = std::sqrt( sum );

    return sum;
}