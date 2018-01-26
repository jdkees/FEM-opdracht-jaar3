/*
 * FEMmetal.h
 *
 *  Created on: Jan 23, 2018
 *      Author: majernik
 *
 * This class models the 2D time-dependent heat equation on a piece of metal.
 * This is class is/was used to test the code.
*/
#ifndef FEMMETAL_H_
#define FEMMETAL_H_

#include <iostream>
#include <string>
#include "FEMobject.h"
#include "ReadFromOBJ.h"
#include "DenseMatrix.h"
#include "FEMelement.h"

class FEMmetal
{
private:
	ReadFromOBJ mesh;
	FEMobject object;
	std::string path;

	double timeStep;
	double T0;
	double c1 = 1;
	double c2 = 1;
	double c3 = 1;
	DenseMatrix C;
	DenseMatrix Kd;
	DenseMatrix Kd_a;
	DenseMatrix Kd_b;
	double a1;
	double a2;
	double a3;
	double b1;
	double b2;
	double b3;


	void evalKDmatrix(int elementIndex);

public:
	FEMmetal(double timeStep, double T0, std::string path);
	void setTemperatureNode(int node, double temp);
	void assemble();
	void nextTimeStep();
	void setConstants(double specificHeat, double density, double thermalConductivity);
	FEMobject* getFEMobject();
	virtual ~FEMmetal();
	void init();
};

#endif /* FEMMETAL_H_ */
