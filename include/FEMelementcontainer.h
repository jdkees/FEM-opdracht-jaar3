/*
 * FEMelementcontainer.h
 *
 *  Created on: Jul 6, 2017
 *      Author: majernik
 *
 * This class stores the element number in a elementVector and the matrix number
 * in the FEMelent class together of matrices with a certain label text.
 * These stored matrices can be used when a operator is needed to applied on all
 * matrices with that specific label.
 */

#ifndef FEMELEMENTCONTAINER_H_
#define FEMELEMENTCONTAINER_H_
#include "DenseMatrix.h"
#include "FEMelement.h"
#include <vector>
#include <string>

class FEMelementcontainer
{
	std::vector<FEMelement*> *elements = nullptr;
	std::string label;

	std::vector<int> elementsIndex;
	std::vector<int> matrixIndex;

public:
	FEMelementcontainer(std::vector<FEMelement*> *elements, std::string label);
	FEMelement* at(int i);
	DenseMatrix* matrixAt(int i);
	int numberOfFoundElements();

	// Matrix manipulations.
	void transpose();
	void conjugate();
	void adjoint();
	void inverse();
	void determinant();
	void add(DenseMatrix m);
	void substract(DenseMatrix m);
	void multiply(DenseMatrix m);
	void multiply(double d);


	virtual ~FEMelementcontainer();
};

#endif /* FEMELEMENTCONTAINER_H_ */
