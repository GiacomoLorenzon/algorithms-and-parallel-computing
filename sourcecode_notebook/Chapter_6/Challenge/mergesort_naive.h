#ifndef _MERGESORT_NAIVE
#define _MERGESORT_NAIVE

#include "utils.h"

namespace msn {

// "Naive" merge sort algorithm implementation

// Merge sort function
// PARAMETERS:
//    vect: the vector to be sorted
// RETURN VALUE: none; vect will be modified
void mergesort ( vector<val_t> &vect );

// Merges two halves of a vector
// PARAMETERS:
//    src1, src2: vectors to be merged
//    dest: reference to the vector into which src1 and src2 will be merged
// RETURN VALUE: none; dest will be overwritten with the result of
//    merging src1 and src2
void merge ( const vector<val_t> &src1, const vector<val_t> &src2, vector<val_t> &dest );

}

#endif
