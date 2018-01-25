/*
 * TriangleInterpolation.h
 *
 *  Created on: Jan 25, 2018
 *      Author: majernik
 *
 * Class is used to interpolate values inside triangle elements.
 * The class Interpolator is inherited.
 */

#ifndef TRIANGLEINTERPOLATION_H_
#define TRIANGLEINTERPOLATION_H_

#include "Interpolator.h"
#include "DenseMatrix.h"

class TriangleInterpolation : public Interpolator
{
private:
	DenseMatrix A;
	DenseMatrix B;
	DenseMatrix C;

	DenseMatrix mP;			// Coordinates of point P.

	void P(double w1, double w2);
	double calculateScalar(int nElm);

public:
	TriangleInterpolation(FEMobject * fem, double dw1, double dw2, double dw3, int globalMatrixIndex);
	virtual ~TriangleInterpolation();

	void interpolate(fieldType t);
};

#endif /* TRIANGLEINTERPOLATION_H_ */
