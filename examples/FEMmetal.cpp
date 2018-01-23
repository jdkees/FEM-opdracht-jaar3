/*
 * FEMmetal.cpp
 *
 *  Created on: Jan 23, 2018
 *      Author: majernik
 */

#include "FEMmetal.h"

FEMmetal::FEMmetal(double timeStep) : timeStep(timeStep)
{
	init();
}

FEMmetal::~FEMmetal() {
	// TODO Auto-generated destructor stub
}


void FEMmetal::init()
{
	// Read and parse the .obj file.
		ReadFromOBJ mesh("./3Dfiles/test.obj");
		mesh.parse();

	// Create a FEM object from the .obj file.
		FEMobject object(&mesh, elementType::TRIANGLES, 2);

	// Calculate the C-matrix for every element.
		C.resize(3, 3);

		C(1,1) = 2;
		C(1,2) = 1;
		C(1,3) = 1;

		C(2,1) = 1;
		C(2,2) = 2;
		C(2,3) = 1;

		C(3,1) = 1;
		C(3,2) = 1;
		C(3,3) = 2;

		for(int i = 0; i < object.getNumberOfElements(); i++)
		{
			DenseMatrix c;
			c = C * object.element(i)->getArea() * (1/12.0);

			object.element(i)->addElementMatrix(c, "C");
		}



}




