#include "utils.h"

// Print vector
ostream& operator<< ( ostream& out, const vector<val_t> &c ) {
   auto i = c.begin();
   for ( ; i != c.end() - 1; ++i )
      out << *i << " ";
   out << *i;

   return out;
}

// Check if a vector is sorted
bool is_sorted ( vector<val_t>::const_iterator start, vector<val_t>::const_iterator end ) {
   for ( auto i = start; i < end - 1; ++i )
      if ( *i > *(i+1) ) return false;

   return true;
}
