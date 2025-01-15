#include "mergesort_naive.h"

namespace msn {

// Merge sort function
void mergesort ( vector<val_t> &vect ) {
   if ( vect.size() <= 1 ) return;
   vector<val_t> v1, v2;

   unsigned int i = 0;
   for ( ; i < vect.size() / 2; ++i ) v1.push_back ( vect[i] );
   for ( ; i < vect.size(); ++i ) v2.push_back ( vect[i] );

   msn::mergesort ( v1 );
   msn::mergesort ( v2 );

   msn::merge ( v1, v2, vect );
}

// Merge
void merge ( const vector<val_t> &src1, const vector<val_t> &src2, vector<val_t> &vect ) {
   auto cur = vect.begin();
   auto it1 = src1.begin();
   auto it2 = src2.begin();

   // Make sure vect is large enough
   if ( vect.size() < src1.size() + src2.size() )
      vect.resize ( src1.size() + src2.size(), 0 );

   while ( it1 != src1.end() && it2 != src2.end() ) {
      if ( *it1 <= *it2 ) {
         *cur = *it1;
         it1++; cur++;
      }

      else {
         *cur = *it2;
         it2++; cur++;
      }
   }

   while ( it1 != src1.end() ) {
      *cur = *it1;
      it1++; cur++;
   }

   while ( it2 != src2.end() ) {
      *cur = *it2;
      *it2++; cur++;
   }
}

}
