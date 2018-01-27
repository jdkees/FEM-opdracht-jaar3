//============================================================================
// Name        : FEM3.cpp
// Author      : Jan Dezider Kees Koomen-Majernik
// Version     :
// Copyright   : 
// Description : This is the main cpp file.
//============================================================================




#include <iostream>
#include "FEMmetal.h"
#include "FEMelement.h"
#include "TriangleInterpolation.h"
using namespace std;

// Defining shape functions.
double N1(FEMelement * elm, double x, double y, double z)
{
	double ans = 0;
	double x1 = elm->getX(0);
	double x2 = elm->getX(1);
	double x3 = elm->getX(2);

	double y1 = elm->getY(0);
	double y2 = elm->getY(1);
	double y3 = elm->getY(2);

	ans = ( 1.0/(2.0*elm->getArea()) )
			*(      (x2*y3-x3*y2)+
					(y2-y3)*x+
					(x3-x2)*y);

	return ans;
}

double N2(FEMelement * elm, double x, double y, double z)
{
	double ans = 0;
	double x1 = elm->getX(0);
	double x2 = elm->getX(1);
	double x3 = elm->getX(2);

	double y1 = elm->getY(0);
	double y2 = elm->getY(1);
	double y3 = elm->getY(2);

	ans = ( 1.0/(2.0*elm->getArea()) )
			*(      (x3*y1-x1*y3)+
					(y3-y1)*x+
					(x1-x3)*y);

	return ans;
}

double N3(FEMelement * elm, double x, double y, double z)
{
	double ans = 0;
	double x1 = elm->getX(0);
	double x2 = elm->getX(1);
	double x3 = elm->getX(2);

	double y1 = elm->getY(0);
	double y2 = elm->getY(1);
	double y3 = elm->getY(2);

	ans = ( 1.0/(2.0*elm->getArea()) )
			*(      (x1*y2-x2*y1)+
					(y1-y2)*x+
					(x2-x1)*y);

	return ans;
}


int main()
{
	cout.precision(4);

	FEMmetal metalBar(1.0, 37.0, "./3Dfiles/test4.obj");

	metalBar.setConstants(90, 2700, 230); 		// Terug zetten naar originele waarde van 900.
	metalBar.init();

	metalBar.setTemperatureNode(1, 100.0);
	metalBar.setTemperatureNode(123, 100.0);
	metalBar.setTemperatureNode(2, 100.0);
	metalBar.setTemperatureNode(128, 100.0);
	metalBar.setTemperatureNode(3, 100.0);
	metalBar.setTemperatureNode(132, 100.0);
	metalBar.setTemperatureNode(4, 100.0);
	metalBar.setTemperatureNode(136, 100.0);
	metalBar.setTemperatureNode(5, 100.0);

	metalBar.setTemperatureNode(201, -80);
	metalBar.setTemperatureNode(36, -80.0);
	metalBar.setTemperatureNode(203, -80.0);
	metalBar.setTemperatureNode(37, -80.0);
	metalBar.setTemperatureNode(202, -80.0);
	metalBar.setTemperatureNode(26, -80.0);
	metalBar.setTemperatureNode(172, -80.0);
	metalBar.setTemperatureNode(25, -80.0);
	metalBar.setTemperatureNode(199, -80.0);

	metalBar.setTemperatureNode(62, 500.0);
	metalBar.setTemperatureNode(63, 500.0);
	metalBar.setTemperatureNode(273, 500.0);
	metalBar.setTemperatureNode(275, 500.0);
	metalBar.setTemperatureNode(276, 500.0);
	metalBar.setTemperatureNode(277, 500.0);
	metalBar.setTemperatureNode(304, 500.0);
	metalBar.setTemperatureNode(307, 500.0);
	metalBar.setTemperatureNode(306, 500.0);


	metalBar.assemble();

	std::cout << ">> Start performing finite difference." <<std::endl;
	std::cout << "Progress: 00.0%" << std::flush;
	int maxIterations = 10000;
	for(int i = 0; i < maxIterations; i++)
	{
		metalBar.nextTimeStep();
		metalBar.setTemperatureNode(1, 500.0);
		metalBar.setTemperatureNode(123, 500.0);
		metalBar.setTemperatureNode(2, 500.0);
		metalBar.setTemperatureNode(128, 500.0);
		metalBar.setTemperatureNode(3, 500.0);
		metalBar.setTemperatureNode(132, 500.0);
		metalBar.setTemperatureNode(4, 500.0);
		metalBar.setTemperatureNode(136, 500.0);
		metalBar.setTemperatureNode(5, 500.0);

		metalBar.setTemperatureNode(201, -80.0);
		metalBar.setTemperatureNode(36, -80.0);
		metalBar.setTemperatureNode(203, -80.0);
		metalBar.setTemperatureNode(37, -80.0);
		metalBar.setTemperatureNode(202, -80.0);
		metalBar.setTemperatureNode(26, -80.0);
		metalBar.setTemperatureNode(172, -80.0);
		metalBar.setTemperatureNode(25, -80.0);
		metalBar.setTemperatureNode(199, -80.0);

		metalBar.setTemperatureNode(62, 500.0);
		metalBar.setTemperatureNode(63, 500.0);
		metalBar.setTemperatureNode(273, 500.0);
		metalBar.setTemperatureNode(275, 500.0);
		metalBar.setTemperatureNode(276, 500.0);
		metalBar.setTemperatureNode(277, 500.0);
		metalBar.setTemperatureNode(304, 500.0);
		metalBar.setTemperatureNode(307, 500.0);
		metalBar.setTemperatureNode(306, 500.0);

		std::cout << "\r" << std::flush;
		std::cout << "                       "<< std::flush;
		std::cout << "\r"<< std::flush;
		std::cout << "Progress: " << (double(i+1)/maxIterations)*100.000 << "%" <<std::flush;
	}
	std::cout <<std::endl;
	std::cout << ">> Completed finite difference."<< std::endl;

	//std:: cout << metalBar.getFEMobject()->global("Ti+1")->matrix << std::endl;

	// Interpolate values inside the elements.
	TriangleInterpolation inter(metalBar.getFEMobject(), 0.1, 0.1, 0.1, 0);
	inter.addShapeFunction(N1);
	inter.addShapeFunction(N2);
	inter.addShapeFunction(N3);
	inter.interpolate(SCALAR);

	// Save the ScalarData class as .CSV file.
	inter.getScalarData()->saveAsCSVfile("kut.CSV");







	std::cout << "=== FINISHED === "<< std::endl;
	return 0;
}
