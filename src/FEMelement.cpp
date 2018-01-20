/*
 * FEMelement.cpp
 *
 *  Created on: Jul 5, 2017
 *      Author: majernik
 */

#include "FEMelement.h"
#include <iostream>

FEMelement::FEMelement()
{
	normal.resize(3, 1);
}

FEMelement::FEMelement(int facenumber, bool boundry)
						: facenumber(facenumber), boundryElement(boundry)
{
	normal.resize(3, 1);
}

void FEMelement::addElementMatrix(DenseMatrix m, std::string label)
{
	elementMatrices.push_back(m);
	labelElementMatrices.push_back(label);
}


void FEMelement::setNormal(DenseMatrix normal)
{
	this->normal = normal;
}

void FEMelement::setFacenumber(int n)
{
	this->facenumber = n;
}


void FEMelement::setArea(double area)
{
	this->area = area;
}

void FEMelement::setBoundry(bool boundry)
{
	boundryElement = boundry;
}

void FEMelement::addVertex(int vertexNo, double* x, double* y, double* z)
{
	vertexNumbers.push_back(vertexNo);

	this->x.push_back(x);
	this->y.push_back(y);
	this->z.push_back(z);
}

DenseMatrix *FEMelement::getElementMatrix(std::string label)
{
	for(int i = 0; i < labelElementMatrices.size(); i++)
	{
		if(labelElementMatrices.at(i) == label)
		{
			return &elementMatrices.at(i);
		}
	}
}

DenseMatrix* FEMelement::getElementMatrix(int id)
{
	return &elementMatrices.at(id);
}

DenseMatrix* FEMelement::getNormal()
{
	return &normal;
}

int FEMelement::getFacenumber()
{
	return facenumber;
}


double FEMelement::getArea()
{
	return area;
}

bool FEMelement::isBoundryElement()
{
	return boundryElement;
}

double FEMelement::getX(int index)
{
	return *x.at(index);
}

double FEMelement::getY(int index)
{
	return *y.at(index);
}

double FEMelement::getZ(int index)
{
	return *z.at(index);
}

int FEMelement::getLabelIndex(std::string label)
{
	for(int i = 0; i < labelElementMatrices.size(); i++)
	{
		if(label == labelElementMatrices.at(i))
		{
			//std::cout << labelElementMatrices.at(i) << std::endl;
			return i;
		}
	}

	// Return not found.
	return -1;
}

int FEMelement::getNumberOfMatrices()
{
	return labelElementMatrices.size();
}

std::string FEMelement::getLabelName(int index)
{
	return labelElementMatrices.at(index);
}

std::vector<int>* FEMelement::getVertexNumbers()
{
	return &vertexNumbers;
}

FEMelement::~FEMelement()
{
	// TODO Auto-generated destructor stub
}

