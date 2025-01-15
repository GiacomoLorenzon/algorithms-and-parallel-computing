#include "Box.hpp"
#include <vector>
int main(void)
{
  // Initialize a couple of Box objects

    Box b1(10,10,10);
    Box b2(10,20,30);
    Box b3(5,5,5);
    Box b4(1,3,6);
    Box b5(b4);
    
    cout << endl;
    double v1 = b1.Volume();
    cout << "volume of box 1 (10x10x10) is: " << v1 << endl;
    cout << "box id: " << b1.getid() << endl;
    cout << endl;
    
    double v2 = b2.Volume();
    cout << "volume of box 2 (10x20x30) is: " << v2 << endl;
    cout << "box id: " << b2.getid() << endl;
    cout << endl;
    
    double v3 = b3.Volume();
    cout << "volume of box 3 (5x5x5) is: " << v3 << endl;
    cout << "box id: " << b3.getid() << endl;
    cout << endl;
    
    double v4 = b4.Volume();
    cout << "volume of box 4 (1x3x6) is: " << v4 << endl;
    cout << "box id: " << b4.getid() << endl;
    cout << endl;
    
    double v5 = b5.Volume();
    cout << "box 5 is equal to box 4" << endl;
    cout << "volume of box 5 is: " << v5 << endl;
    cout << "box id: " << b5.getid() << endl;
    cout << endl;
    
    cout << "now box 5 is equal to box 3" << endl;
    b5 = b3;
    double v6 = b5.Volume();
    cout << "new volume of box 5 is: " << v6 << endl;
    cout << "new box id: " << b5.getid() << endl;
    cout << endl;
    
  // Print total number of objects bellow
      
    unsigned tot_count = Box::getcount();
    cout << "the total number of boxes is: " << tot_count << endl;
    
  return 0;
}
