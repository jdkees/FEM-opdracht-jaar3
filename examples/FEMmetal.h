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
#include "FEMobject.h"
#include "ReadFromOBJ.h"
#include "DenseMatrix.h"

class FEMmetal
{
private:
	double timeStep;
	DenseMatrix C;

	void init();

public:
	FEMmetal(double timeStep);
	virtual ~FEMmetal();
};

#endif /* FEMMETAL_H_ */
