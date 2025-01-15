#ifndef BOX_hpp
#define BOX_hpp

#include <iostream>
using std::cout;
using std::endl;

class Box
{
public:

    Box(double l, double b, double h): length(l),breadth(b),height(h)
    {
      cout <<"Constructing a box"<< endl;
      count ++;
      id = count;
    }
      
    // copy constructor
    Box(const Box & b): length(b.length),breadth(b.breadth),height(b.height)
    {
      cout <<"Using copy constructor"<< endl;
      count ++;
      id = count;
    }
    
    // member functions
    double Volume() const;
    static unsigned getcount() {return count;}
    unsigned getid() const {return id;}

    // assignement operator
    Box& operator=(const Box &);

private:
    double length; // Length of a box
    double breadth; // Breadth of a box
    double height; // Height of a box
    unsigned id;  // Identification Number of the box
    static unsigned count; // Number of boxes
};

#endif
