//============================================================================
// Name        : KMeans.cpp
// Author      : Danilo
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "Clustering.hpp"

int main() 
{
	Clustering c(2,10,2,10000);
	c.print();
	c.calc_cluster();
	c.print();

	return 0;
}
