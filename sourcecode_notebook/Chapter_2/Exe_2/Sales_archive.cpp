#include "Sales_archive.h"

using std::vector;
using std::string;

// public methods:
vector<Sales_data>::const_iterator
Sales_archive::find_isbn (const string &s) const
{
    vector<Sales_data>::const_iterator pos = archive.cbegin();
    while (pos!=archive.cend() && pos->isbn()!=s)
        pos++;
    return pos;    
}    
    
Sales_archive
Sales_archive::reduce_by_book (void) const
{
    vector<Sales_data>::const_iterator cit = archive.cbegin();
    Sales_data sd = *cit;
    Sales_archive new_sa(sd);
    for (cit=archive.cbegin()+1; cit!=archive.cend(); cit++)
      {
        sd = *cit;
        vector<Sales_data>::iterator pos = new_sa.find_isbn(sd.isbn());
        if (pos==new_sa.archive.end())
            new_sa.archive.push_back(sd);
        else
            pos->combine(sd);    
      }
    return new_sa;   
}
    
void
Sales_archive::print_archive (void) const
{
    vector<Sales_data>::const_iterator cit;
    for (cit=archive.cbegin(); cit!=archive.cend(); cit++)
        cit->print();
}
    
// private methods: 
vector<Sales_data>::iterator
Sales_archive::find_isbn (const string &s)
{
    vector<Sales_data>::iterator pos = archive.begin();
    while (pos!=archive.end() && pos->isbn()!=s)
        pos++;
    return pos;    
}  
