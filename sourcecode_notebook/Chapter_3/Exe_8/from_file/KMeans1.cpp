//============================================================================
// Name        : KMeans.cpp
// Author      : Danilo
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "Clustering1.hpp"

int main() 
{
	Clustering c(2,10,2,10000,"coords.txt");
	c.print();
	c.calc_cluster();
	c.print();

	return 0;
}
