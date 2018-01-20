//============================================================================
// Name        : FEM3.cpp
// Author      : Jan Dezider Kees Koomen-Majernik
// Version     :
// Copyright   : 
// Description : This is the main cpp file.
//============================================================================

#include <iostream>
#include "DenseMatrix.h"
#include "Calculus.h"
using namespace std;


double f(double x/*, double y, double z*/)
{
	return log(pow(x, 2))*pow(x, 2);
}

int main() {
	DenseMatrix test;
	test.resize(2, 2);
	test.matrix << 1, 2,
			       3, 4;

	DenseMatrix hoer;
	hoer.resize(2, 2);
	hoer.matrix << 5, 6,
			       7, 8;

	DenseMatrix ans;
	ans.resize(2, 2);
	ans = hoer + test;


	ans.print();



	return 0;
}
