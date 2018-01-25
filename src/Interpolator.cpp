/*
 * Interpolator.cpp
 *
 *  Created on: Jul 27, 2017
 *      Author: majernik
 */

#include "Interpolator.h"
#include <iostream>


Interpolator::Interpolator(FEMobject * fem, double dx, double dy, double dz)
{
	setFEMobject(fem);
	setStepsize(dx, dy, dz);
}

void Interpolator::setFEMobject(FEMobject* fem)
{
	this->fem = fem;
}

void Interpolator::addShapeFunction(
		double (*shapeFunction)(FEMelement*, double, double, double))
{
	functionContainer.push_back(shapeFunction);
	numberOfShapefunctions++;
}

void Interpolator::setStepsize(double dx, double dy, double dz)
{
	this->dx = dx;
	this->dy = dy;
	this->dz = dz;
}

void Interpolator::setGlobalMatrixIndex(int index)
{
	globalMatrixIndex = index;
}



ScalarData* Interpolator::getScalarData()
{
	return &scalarData;
}

VectorData* Interpolator::getVectorData()
{
	return &vectorData;
}

Interpolator::~Interpolator()
{
	// TODO Auto-generated destructor stub
}

