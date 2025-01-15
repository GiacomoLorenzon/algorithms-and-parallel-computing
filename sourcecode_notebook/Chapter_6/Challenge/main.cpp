#include <iostream>
#include <ctime>

#include "mergesort_queue.h"
#include "mergesort_naive.h"

using std::cout;
using std::endl;

int main () {
   const unsigned int N = 5000;
   clock_t t1 = 0, t2 = 0;

   cout << "TEST 1: reverse order vector" << endl;
   vector<val_t> v = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
   cout << "  Before sorting: " << v << endl;
   msq::mergesort ( v.begin(), v.size() );
   cout << "   After sorting: " << v << endl;

   cout << "\nTEST 2: sorting large vectors, naive vs. optimized" << endl;

   // Generating two copies of a vector of N elements for testing purposes
   vector<val_t> v1(N), v2(N);
   for ( unsigned int i = 0; i < N; ++i ) v2[i] = v1[i] = N - i;

   // Sorting the vector with the two algorithms, taking the time and comparing

   // Optimized
   t1 = clock();
   msq::mergesort ( v1.begin(), v1.size() );
   t2 = clock();
   double opt = double(t2 - t1)/CLOCKS_PER_SEC;

   // Naive
   t1 = clock();
   msn::mergesort ( v2 );
   t2 = clock();
   double naive = double(t2 - t1)/CLOCKS_PER_SEC;

   printf ( "      Naive: %.4fs\n  Optimized: %.4fs (%.2f%%)\n", naive, opt, (opt-naive)/naive*100 );

   return 0;
}
