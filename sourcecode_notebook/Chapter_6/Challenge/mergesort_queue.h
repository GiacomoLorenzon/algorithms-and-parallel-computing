#ifndef _MERGESORT_QUEUE
#define _MERGESORT_QUEUE

#include "utils.h"
#include <queue>

using std::queue;

namespace msq {

// Merge sort algorithm with optimized memory usage by Lorenzo Fiorentini
// The merge function was modified to make use of queue container

// Merge sort function
// PARAMETERS:
//    start: iterator to the beginning of the vector to be sorted
//    size: size of the vector to be sorted
// RETURN VALUE: none; the vector containing the element pointed by start will
//    be modified
void mergesort ( vector<val_t>::iterator start, unsigned int size );

// Merges two halves of a vector
// PARAMETERS:
//    start: iterator to the beginning of the vector containing the two halves
//    end1: iterator to the one-past-end element of the first half
//    end2: iterator to the one-past-end element of the second half
// RETURN VALUE: none; the vector to which the iterators refer is modified
// NOTES: the halves are assumed to be already sorted when calling this function;
//    moreover, we assume the iterators all point to elements in the same vector
void merge ( vector<val_t>::iterator start, vector<val_t>::iterator end1, vector<val_t>::iterator end2 );

}

#endif
