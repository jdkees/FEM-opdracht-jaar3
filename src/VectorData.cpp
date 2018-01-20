/*
 * VectorData.cpp
 *
 *  Created on: Jul 27, 2017
 *      Author: majernik
 */

#include "VectorData.h"

VectorData::VectorData() {
	// TODO Auto-generated constructor stub

}

void VectorData::setVectorData(double x, double y, double z, DenseMatrix vec)
{
	this->x.push_back(x);
	this->y.push_back(y);
	this->z.push_back(z);
	this->vec.push_back(vec);

	sizeVecticesVector++;
	sizeVecVector++;
}

DenseMatrix VectorData::getVector(int index)
{
	return vec.at(index);
}

double VectorData::getX(int index)
{
	return x.at(index);
}

double VectorData::getY(int index)
{
	return y.at(index);
}

double VectorData::getZ(int index)
{
	return z.at(index);
}

VectorData::~VectorData() {
	// TODO Auto-generated destructor stub
}

