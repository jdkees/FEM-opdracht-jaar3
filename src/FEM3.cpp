//============================================================================
// Name        : FEM3.cpp
// Author      : Jan Dezider Kees Koomen-Majernik
// Version     :
// Copyright   : 
// Description : This is the main cpp file.
//============================================================================

#include <iostream>
#include "FEMmetal.h"
using namespace std;


int main()
{
	FEMmetal metalBar(0.1, 5.0, 37);
	metalBar.assemble();


	std::cout << "=== FINISHED === "<< std::endl;
	return 0;
}
