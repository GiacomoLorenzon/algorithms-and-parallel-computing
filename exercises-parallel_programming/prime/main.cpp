#include <iostream>
#include <cmath>
#include <mpi.h>
#include <vector>

std::vector<unsigned> get_prime_numbers(unsigned min, unsigned max);
bool is_prime (unsigned n);

int main (int argc, char* argv[])
{
// init
    MPI_Init(&argc, &argv);
// initialize rank and size
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
// read parameters from command-line
    unsigned min = std::stoi(argv[1]);
    unsigned max = std::stoi(argv[2]);
// get the vector of prime numbers
    std::vector<unsigned> prime_numbers = get_prime_numbers(min, max);
// rank 0 prints the prime numbers
    if (rank == 0)
    {
        std::cout << "prime numbers between " << min << " and " << max
                  << " are:" << std::endl;
        for (unsigned n : prime_numbers)
            std::cout << n << " ";
        std::cout << std::endl;
    }
// finalize
    MPI_Finalize();
    return 0;
}

std::vector<unsigned> get_prime_numbers(unsigned min, unsigned max)
{
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    std::vector<unsigned> local_prime;

    for ( unsigned i = min + rank; i <= max; i += size )
        if ( is_prime( i ) )
            local_prime.push_back( i );

    unsigned local_l = local_prime.size();
    unsigned l_max;

    MPI_Allreduce( &local_l, &l_max, 1, MPI_UNSIGNED, MPI_MAX, MPI_COMM_WORLD );

    std::vector<unsigned> prime( size * l_max, 0 );

    local_prime.resize(l_max);
    MPI_Allgather( &local_prime[0], l_max, MPI_UNSIGNED,
                   &prime[0], size * l_max, MPI_UNSIGNED,
                   MPI_COMM_WORLD);

    std::vector<unsigned> v;

    for ( unsigned n : prime)
        if ( n != 0 )
            v.push_back( n );

    return v;
}

bool is_prime (unsigned n)
{
    if(n<=1)
        return false;
    for (int i = 2; i <= sqrt(n); i++)
        if (n % i == 0)
            return false;

    return true;
}