#include "mergesort_queue.h"

namespace msq {

// Merge sort function
void mergesort ( vector<val_t>::iterator start, unsigned int size ) {
   // If size == 1, then the vector is already sorted 
   if ( size == 1 ) return;

   // If size == 2, we only have to compare the two elements and swap them
   // if necessary
   if ( size == 2 ) {
      if (*start > *(start+1)) {
         val_t swap = *start;
         *start = *(start+1);
         *(start+1) = swap;
      }

      return;
   }

   // If the vector is sorted already, we do nothing more
   if ( is_sorted ( start, start + size ) )
      return;

   // If not, we split the vector into two halves and separately sort them
   unsigned int size1 = size / 2,
                size2 = size - size1;

   msq::mergesort ( start, size1 );
   msq::mergesort ( start + size1, size2 );

   // Finally, we merge the two halves
   msq::merge ( start, start + size1, start + size );
}

// Merge two halves of a vector
void merge ( vector<val_t>::iterator start, vector<val_t>::iterator end1, vector<val_t>::iterator end2 ) {
   queue<val_t> support;

   // If either half is empty, the vector is already sorted
   if ( start == end1 || start == end2 )
      return;

   // If all elements of the first half are smaller than the smallest (i.e.
   // the first, end1) element of the second, then the two halves are already
   // sorted
   auto it1 = start;
   for ( ; it1 != end1; ++it1 )
      if ( *it1 > *end1 ) break;
   if ( it1 == end1 ) return;

   // At this point, it1 refers to the first element in the first half that
   // is larger than the smallest element in the second half (i.e. end1)

   // We use the support queue to temporarily store elements that are removed
   // from the first half because they're larger than the current element
   // on the second half

   auto it2 = end1; // Iterator for the second half
   while ( it1 != end1 && it2 != end2 ) {
      // If we have nothing in the support queue, we just compare the two
      // current elements in each half
      if ( support.empty() ) {
         if ( *it2 <= *it1 ) {
            support.push(*it1);
            *it1 = *it2; it1++;
            it2++;
         }

         else {
            it1++;
         }
      }

      // If we have at least one element in the support queue, we also have
      // to compare the current elements with the support element, and
      // insert the smallest one into the vector
      else {
         // Support has the smallest
         if ( support.front() <= *it1 && support.front() <= *it2 ) {
            support.push(*it1);
            *it1 = support.front(); it1++;
            support.pop();
         }

         // Second half has the smallest
         else if ( *it2 <= support.front() && *it2 <= *it1 ) {
            support.push(*it1);
            *it1 = *it2; it1++;
            it2++;
         }

         // First half has the smallest
         else if ( *it1 <= support.front() && *it1 <= *it2 ) {
            it1++;
         }
      }
   }

   // At this point, the second half of the vector might still contain some
   // elements, which we'll have to compare with those in the support queue
   while ( it2 != end2 && !support.empty() && it1 != end2 ) {
      // Support has the smallest
      if ( support.front() <= *it2 ) {
         *it1 = support.front(); it1++;
         support.pop();
      }

      // Second half has the smallest
      else {
         *it1 = *it2; it1++;
         it2++;
      }
   }

   // Finally, there might be some elements left in the support queue. We
   // can just push them to our vector
   while ( !support.empty() ) {
      *it1 = support.front(); it1++;
      support.pop();
   }
}

}
