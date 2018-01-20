/*
 * FEMelementcontainer.cpp
 *
 *  Created on: Jul 6, 2017
 *      Author: majernik
 */

#include "FEMelementcontainer.h"
#include <stdexcept>
#include <iostream>

FEMelementcontainer::FEMelementcontainer(std::vector<FEMelement*> *elements, std::string label)
										: elements(elements), label(label)
{
	// Go through all the elements and check for the label.
	for(int i = 0; i < elements->size(); i++)
	{
		for(int j = 0; j < elements->at(i)->getNumberOfMatrices(); j++ )
		{
			if(elements->at(i)->getLabelName(j) == label)
			{
				//std::cout << "Element "<< i << " label: " << elements->at(i).getLabelName(j) << std::endl;
				elementsIndex.push_back(i);
				matrixIndex.push_back(j);
			}
		}
	}

	if(elementsIndex.size() == 0)
	{
		throw std::runtime_error("Element label:\""+label+"\" not found ");
	}
}

FEMelement* FEMelementcontainer::at(int i)
{
	int elementIndex = elementsIndex.at(i);

	return elements->at(elementIndex);
}

DenseMatrix* FEMelementcontainer::matrixAt(int i)
{
	int IelementIndex = elementsIndex.at(i);
	int ImatrixIndex = matrixIndex.at(i);

	return elements->at(IelementIndex)->getElementMatrix(ImatrixIndex);
}

int FEMelementcontainer::numberOfFoundElements()
{
	return elementsIndex.size();
}

void FEMelementcontainer::transpose()
{
	int elementMatrixIndex;
	for(int i = 0; i < elementsIndex.size(); i++)
	{
		elementMatrixIndex = matrixIndex.at(i);

		elements->at(i)->getElementMatrix(elementMatrixIndex)->transpose();
	}
}

void FEMelementcontainer::conjugate()
{
	int elementMatrixIndex;
	for(int i = 0; i < elementsIndex.size(); i++)
	{
		elementMatrixIndex = matrixIndex.at(i);

		elements->at(i)->getElementMatrix(elementMatrixIndex)->conjugate();
	}
}

void FEMelementcontainer::adjoint()
{
	int elementMatrixIndex;
	for(int i = 0; i < elementsIndex.size(); i++)
	{
		elementMatrixIndex = matrixIndex.at(i);

		elements->at(i)->getElementMatrix(elementMatrixIndex)->adjoint();
	}
}

void FEMelementcontainer::inverse()
{
	int elementMatrixIndex;
	for(int i = 0; i < elementsIndex.size(); i++)
	{
		elementMatrixIndex = matrixIndex.at(i);

		elements->at(i)->getElementMatrix(elementMatrixIndex)->inverse();
	}
}

void FEMelementcontainer::determinant()
{
}

void FEMelementcontainer::add(DenseMatrix m)
{
	int elementMatrixIndex;
	for(int i = 0; i < elementsIndex.size(); i++)
	{
		elementMatrixIndex = matrixIndex.at(i);

		elements->at(i)->getElementMatrix(elementMatrixIndex)->add(m);
	}
}

void FEMelementcontainer::substract(DenseMatrix m)
{
	int elementMatrixIndex;
	for(int i = 0; i < elementsIndex.size(); i++)
	{
		elementMatrixIndex = matrixIndex.at(i);

		elements->at(i)->getElementMatrix(elementMatrixIndex)->substract(m);
	}
}

void FEMelementcontainer::multiply(DenseMatrix m)
{
	int elementMatrixIndex;
	for(int i = 0; i < elementsIndex.size(); i++)
	{
		elementMatrixIndex = matrixIndex.at(i);

		elements->at(i)->getElementMatrix(elementMatrixIndex)->multiply(m);
	}
}

void FEMelementcontainer::multiply(double d)
{
	int elementMatrixIndex;
	for(int i = 0; i < elementsIndex.size(); i++)
	{
		elementMatrixIndex = matrixIndex.at(i);

		elements->at(i)->getElementMatrix(elementMatrixIndex)->multiply(d);
	}
}



FEMelementcontainer::~FEMelementcontainer()
{
	// TODO Auto-generated destructor stub
}

