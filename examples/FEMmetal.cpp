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
		object.setObjectData(&mesh, elementType::TRIANGLES, 2);

	// Calculate the C-matrix for every element.
		C.resize(3, 3);
		Kd.resize(3, 3);
		Kd_a.resize(3, 3);
		Kd_b.resize(3, 3);

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
		// Calculate the C-matrix and add it to all elements.
			DenseMatrix c;
			c = C * object.element(i)->getArea() * (1/12.0) * c1;;
			object.element(i)->addElementMatrix(c, "C");

		// Calculate the KD-matrix and add it to all elements.
			evalKDmatrix(i);
			object.element(i)->addElementMatrix(Kd, "Kd");

		// Create a Ti matrix for every element. This matrix may contain the values
		// at the boundaries.
			DenseMatrix Ti_e;
			Ti_e.resize(3, 1);
			object.element(i)->addElementMatrix(Ti_e, "Ti_e");
		}

		// Create the global T_i matrix.
		object.addGlobalMatrix(mesh.verticesSize(), 1, "Ti");
		// Create the global T_i+1 matrix.
		object.addGlobalMatrix(mesh.verticesSize(), 1, "Ti+1");

		// Create the global C matrix.
		object.addGlobalMatrix(mesh.verticesSize(), mesh.verticesSize(), "C");
		// Create the global Kd matrix.
		object.addGlobalMatrix(mesh.verticesSize(), mesh.verticesSize(), "Kd");


}

void FEMmetal::setTemperatureBoundaryNode(int elmIndex, int node, double temp)
{
	object.element(elmIndex)->setBoundary(true);

	object.element(elmIndex)->getElementMatrix("Ti_e")->setValue(temp, node, 1);
}



void FEMmetal::evalKDmatrix(int elementIndex)
{
	FEMelement * elm = object.element(elementIndex);

	// Calculate the a_i and b_i.
	a1 = elm->getY(1) - elm->getY(2);
	b1 = elm->getX(2) - elm->getX(1);

	a2 = elm->getY(2) - elm->getY(0);
	b2 = elm->getX(0) - elm->getX(2);

	a3 = elm->getY(0) - elm->getY(1);
	b3 = elm->getX(1) - elm->getX(0);

	// Calculate the Kd_a and Kd_b.
	Kd_a(1, 1) = a1*a1;
	Kd_a(2, 2) = a2*a2;
	Kd_a(3, 3) = a3*a3;

	Kd_a(1, 2) = a1*a2;
	Kd_a(2, 1) = a2*a1;

	Kd_a(1, 3) = a1*a3;
	Kd_a(3, 1) = a3*a1;

	Kd_a(2, 3) = a2*a3;
	Kd_a(3, 2) = a3*a2;

	Kd_b(1, 1) = b1*b1;
	Kd_b(2, 2) = b2*b2;
	Kd_b(3, 3) = b3*b3;

	Kd_b(1, 2) = b1*b2;
	Kd_b(2, 1) = b2*b1;

	Kd_b(1, 3) = b1*b3;
	Kd_b(3, 1) = b3*b1;

	Kd_b(2, 3) = b2*b3;
	Kd_b(3, 2) = b3*b2;

	Kd_a = Kd_a * c2;
	Kd_b = Kd_b * c3;

	// Calculate the Kd matrix.
	Kd = Kd_a + Kd_b;
	Kd = Kd * (-1.0 * timeStep) * (1.0 / (4.0 * elm->getArea()) );
}

void FEMmetal::assemble()
{
	// Assemble the element matrices "C" into the global "C" matrix.
	object.assemble("C", "C");

	// Assemble the element matrices "Kd" into the global "Kd" matrix.
	object.assemble("Kd", "Kd");


	// <<<<<<<<<< Hier straks verder werken.
}




