/*
 * Calculus.h
 *
 *  Created on: Jan 16, 2018
 *      Author: majernik
 */

#ifndef CALCULUS_H_
#define CALCULUS_H_

#include <math.h>

enum integrationMethod {GAUSS_LEGENDRE10};


class Calculus {
private:
	// Points and Weights for the Gauss–Legendre quadrature on the domain [-1, 1].
	double GL10_p[10];
	double GL10_w[10];


public:
	Calculus();
	double NIntegrate3D (integrationMethod method, double (*f)(double, double, double),
						double xmin, double xmax,
						double ymin, double ymax,
						double zmin, double zmax);
	double NIntegrate1D (integrationMethod method, double (*f)(double),
						double xmin, double xmax);
	virtual ~Calculus();
};

#endif /* CALCULUS_H_ */
