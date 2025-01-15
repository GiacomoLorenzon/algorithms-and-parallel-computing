#ifndef _UTILS
#define _UTILS

#include <vector>
#include <ostream>

using std::vector;
using std::ostream;

typedef int val_t;

// Overload output operator, used to print content of containers
ostream& operator<< (ostream&, const vector<val_t>&);

// Check if a vector is sorted or not
// PARAMETERS:
//    start: iterator to the beginning of the vector to be checked
//    end: iterator to the end of the vector to be checked
// RETURN VALUE: true if the vector is sorted in ascending order, false
//    otherwise
bool 
is_sorted (vector<val_t>::const_iterator start, vector<val_t>::const_iterator end);

#endif
