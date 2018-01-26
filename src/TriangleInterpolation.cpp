/*
 * TriangleInterpolation.cpp
 *
 *  Created on: Jan 25, 2018
 *      Author: majernik
 */

#include <TriangleInterpolation.h>

TriangleInterpolation::TriangleInterpolation(FEMobject * fem, double dw1, double dw2, double dw3, int globalMatrixIndex)
: Interpolator(fem, dw1, dw2, dw3)
{
	// Initialize the A, B and C matrices.
	A.resize(3,1);
	B.resize(3,1);
	C.resize(3,1);

	setGlobalMatrixIndex(globalMatrixIndex);

}

TriangleInterpolation::~TriangleInterpolation() {
	// TODO Auto-generated destructor stub
}

void TriangleInterpolation::P(double w1, double w2)
{
	mP = A + (B-A)*w1 + (C-A)*w2;
}

double TriangleInterpolation::calculateScalar(int nElm)
{

	double sc = 0;
	int vertex1 = 0;
	int vertex2 = 0;
	int vertex3 = 0;
	double T1 = 0;
	double T2 = 0;
	double T3 = 0;
	double N1 = 0;
	double N2 = 0;
	double N3 = 0;


	vertex1 = fem->element(nElm)->getVertexNumbers()->at(0)+1;
	vertex2 = fem->element(nElm)->getVertexNumbers()->at(1)+1;
	vertex3 = fem->element(nElm)->getVertexNumbers()->at(2)+1;

	T1 = fem->global(globalMatrixIndex)->getValue(vertex1, 1);
	T2 = fem->global(globalMatrixIndex)->getValue(vertex2, 1);
	T3 = fem->global(globalMatrixIndex)->getValue(vertex3, 1);

	N1 = functionContainer.at(0)( fem->element(nElm), mP.getValue(1,1), mP.getValue(2,1), mP.getValue(3,1) );
	N2 = functionContainer.at(1)( fem->element(nElm), mP.getValue(1,1), mP.getValue(2,1), mP.getValue(3,1) );
	N3 = functionContainer.at(2)( fem->element(nElm), mP.getValue(1,1), mP.getValue(2,1), mP.getValue(3,1) );


	sc = N1*T1 + N2*T2 + N3*T3;

	return sc;
}

void TriangleInterpolation::interpolate(fieldType t)
{
	typeField = t;

	if(t == SCALAR)
	{
		std::cout << ">> Start interpolating elements "<<std::endl;
		std::cout << "Progress: 00.0%"<< std::flush;

		// Iterate through all the elements in the object.
		for(int nElm = 0; nElm < fem->getNumberOfElements(); nElm++ )
		{
			A(1,1) = fem->element(nElm)->getX(0);
			A(2,1) = fem->element(nElm)->getY(0);
			A(3,1) = fem->element(nElm)->getZ(0);

			B(1,1) = fem->element(nElm)->getX(1);
			B(2,1) = fem->element(nElm)->getY(1);
			B(3,1) = fem->element(nElm)->getZ(1);

			C(1,1) = fem->element(nElm)->getX(2);
			C(2,1) = fem->element(nElm)->getY(2);
			C(3,1) = fem->element(nElm)->getZ(2);

			std::cout << "\r"<< std::flush;
			std::cout << "                  "<< std::flush;
			std::cout << "\r"<< std::flush;
			std::cout << "Progress: " << (double(nElm+1)/fem->getNumberOfElements())*100 << "%" << std::flush;

			// Iterate through w1 and w2.
			for(double w1 = 0; w1 < 1; w1=w1+dx)
			{
				for(double w2 = 0; w2 < 1; w2=w2+dy)
				{
					if(w1 + w2 > 1)
					{
						break;
					}else
					{
						// Point P inside triangle.
						P(w1, w2);

						scalarData.setScalarValue(mP.getValue(1,1),
								mP.getValue(2,1),
								mP.getValue(3,1),
								calculateScalar(nElm));

					}
				}
			}
		}

		std::cout <<std::endl;
		std::cout << ">> Completed interpolating elements." << std::endl;

	}
}
