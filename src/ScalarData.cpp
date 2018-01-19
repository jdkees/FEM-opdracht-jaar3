/*
 * ScalarData.cpp
 *
 *  Created on: Jul 18, 2017
 *      Author: majernik
 */

#include "ScalarData.h"
#include <iostream>
#include <fstream>

ScalarData::ScalarData() {
	// TODO Auto-generated constructor stub

}

ScalarData::~ScalarData() {
	// TODO Auto-generated destructor stub
}

void ScalarData::setScalarValue(double x, double y, double z, double scalar)
{
	this->x.push_back(x);
	this->y.push_back(y);
	this->z.push_back(z);

	this->scalar.push_back(scalar);

	sizeScalarVector++;
	sizeVecticesVector++;
}

double ScalarData::getScalar(int index)
{
	return scalar.at(index);
}

double ScalarData::getX(int index)
{
	return x.at(index);
}

double ScalarData::getY(int index)
{
	return y.at(index);
}

double ScalarData::getZ(int index)
{
	return z.at(index);
}

int ScalarData::getSize()
{
	return sizeScalarVector;
}

void ScalarData::printScalarField()
{
	std::cout << "> Printing scalar data." << std::endl;
	for(int n = 0; n < getSize(); n++)
	{
		std::cout << "x=" << getX(n) << "  ";
		std::cout << "y=" << getY(n) << "  ";
		std::cout << "z=" << getZ(n) << "  ";

		std::cout << "scalar value: " << getScalar(n) << std::endl;

	}
}

void ScalarData::saveAsCSVfile(std::string path)
{
	std::ofstream myfile(path);
	if (myfile.is_open())
	{
		for(int i = 0; i < getSize(); i++)
		{
			myfile << getX(i) << "," << getY(i) << "," << getZ(i) << "," <<getScalar(i) << "\n";
		}
		myfile.close();
	}
	else std::cout << "Unable to open file";
}
