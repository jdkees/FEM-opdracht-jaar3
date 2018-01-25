/*
 * Interpolator.h
 *
 *  Created on: Jul 27, 2017
 *      Author: majernik
 *
 * This class forms the basis as a derived class in class inheritance.
 * It offers the basic subroutines for creating a interpolating class
 * for the different elements.
 * This class contains the virtual function "interpolate(fieldType t)"
 * which needs to be overwritten in the interpolation class.
 */

#ifndef INTERPOLATOR_H_
#define INTERPOLATOR_H_
#include "FEMobject.h"
#include "FEMelement.h"
#include "ScalarData.h"
#include "VectorData.h"

#include <vector>
#include <functional>

enum fieldType { SCALAR, VECTOR};

class Interpolator
{
	// Private variables. Not private for inherited classes.
protected:
	FEMobject * fem = nullptr;
	ScalarData scalarData;
	VectorData vectorData;

	double dx = 1.0;
	double dy = 1.0;
	double dz = 1.0;

	std::vector< std::function<double(FEMelement*, double, double, double)> > functionContainer;

	fieldType typeField;

	int globalMatrixIndex;

	int numberOfShapefunctions = 0;


public:
	Interpolator(FEMobject * fem, double dx, double dy, double dz);
	void setFEMobject(FEMobject * fem);
	void setStepsize(double dx, double dy, double dz);
	void setGlobalMatrixIndex(int index);
	void addShapeFunction(double (*shapeFunction)(FEMelement*, double, double, double));
	virtual void interpolate(fieldType t) {};
	ScalarData * getScalarData();
	VectorData * getVectorData();


	virtual ~Interpolator();
};

#endif /* INTERPOLATOR_H_ */
