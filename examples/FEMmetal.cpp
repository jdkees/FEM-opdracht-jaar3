/*
 * FEMmetal.cpp
 *
 *  Created on: Jan 23, 2018
 *      Author: majernik
 */

#include "FEMmetal.h"

FEMmetal::FEMmetal(double timeStep, double T0, std::string path) : timeStep(timeStep),
					T0(T0), path(path)
{

}

FEMmetal::~FEMmetal() {
	// TODO Auto-generated destructor stub
}


void FEMmetal::init()
{
	// Read and parse the .obj file.
		mesh.setFilepath(path);
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
			c = C * object.element(i)->getArea() * (1/12.0) * c1;
			object.element(i)->addElementMatrix(c, "C");


		// Calculate the KD-matrix and add it to all elements.
			evalKDmatrix(i);
			object.element(i)->addElementMatrix(Kd, "Kd");
		}

		// Create the global T_i matrix.
		object.addGlobalMatrix(mesh.verticesSize(), 1, "Ti");
		// Create the global T_i+1 matrix.
		object.addGlobalMatrix(mesh.verticesSize(), 1, "Ti+1");

		// Create the global C matrix.
		object.addGlobalMatrix(mesh.verticesSize(), mesh.verticesSize(), "C");
		// Create the global Kd matrix.
		object.addGlobalMatrix(mesh.verticesSize(), mesh.verticesSize(), "Kd");

		// Fill the Ti matrix with the initial temperature.
		for(int i = 1; i < mesh.verticesSize()+1; i++)
		{
			setTemperatureNode(i, T0);
		}

}

void FEMmetal::setConstants(double specificHeat, double density,
		double thermalConductivity)
{
	c1 = specificHeat * density;
	c2 = thermalConductivity;
	c3 = thermalConductivity;
}


void FEMmetal::setTemperatureNode(int node, double temp)
{
	object.global("Ti")->setValue(temp, node, 1);
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

//	std::cout << "Element matrix C: \n" << object.element(1)->getElementMatrix("C")->matrix << std::endl;
//	std::cout << "Global matrix C: \n" << object.global("C")->matrix << std::endl;
}

void FEMmetal::nextTimeStep()
{
	SparseMatrix interAdd;
	SparseMatrix interMul;
	interAdd = *object.global("Kd") + *object.global("C");
	interMul = interAdd * *object.global("Ti");

	// Solve matrix equation Ax=B.
	*object.global("Ti+1") = object.global("C")->solve(&interMul, CHOLESKY);

	// Ti will be assigned the values of Ti+1 for the next iteration.
	*object.global("Ti") = *object.global("Ti+1");


	//std::cout << object.global("Ti+1")->matrix << std::endl;
}

FEMobject* FEMmetal::getFEMobject()
{
	return &object;
}



