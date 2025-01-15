#ifndef SALES_ARCHIVE_H
#define SALES_ARCHIVE_H

#include <vector>

#include "Sales_data.h"

class Sales_archive {
    
public:
    // constructors:
    Sales_archive (void) = default;
    Sales_archive (const Sales_data &s): archive({s}) {}
    Sales_archive (const std::vector<Sales_data> &v): archive(v) {}
    
    // public methods:
    std::vector<Sales_data>::const_iterator
    find_isbn (const std::string &) const;
    
    void
    add_elem (const Sales_data &sd) {archive.push_back(sd);}
    
    Sales_archive
    reduce_by_book (void) const;
    
    void
    print_archive (void) const;

private:
    std::vector<Sales_data> archive;
    
    // private methods:
    std::vector<Sales_data>::iterator
    find_isbn (const std::string &);

};

#endif /* SALES_ARCHIVE_H */
