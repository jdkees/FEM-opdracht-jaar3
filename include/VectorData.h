/*
 * VectorData.h
 *
 *  Created on: Jul 27, 2017
 *      Author: majernik
 *
 *
 * This class is a datatype. Just as for the ScalarData class, this class stores a
 * vector associated with a coordinate in x, y, and z space.
 */

#ifndef VECTORDATA_H_
#define VECTORDATA_H_
#include <vector>
#include <DenseMatrix.h>

class VectorData
{
private:
	std::vector<double> x;
	std::vector<double> y;
	std::vector<double> z;
	int sizeVecticesVector = 0;

	std::vector<DenseMatrix> vec;
	int sizeVecVector = 0;

public:
	VectorData();
	void setVectorData(double x, double y, double z, DenseMatrix vec);
	DenseMatrix getVector(int index);
	double getX(int index);
	double getY(int index);
	double getZ(int index);

	virtual ~VectorData();
};

#endif /* VECTORDATA_H_ */
