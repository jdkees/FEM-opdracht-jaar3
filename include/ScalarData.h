/*
 * ScalarData.h
 *
 *  Created on: Jul 18, 2017
 *      Author: majernik
 *
 * This class is a datatype for storing a scalar value on a x, y and z coordinate.
 */

#ifndef SCALARDATA_H_
#define SCALARDATA_H_
#include <vector>
#include <string>

class ScalarData
{
private:
	std::vector<double> x;
	std::vector<double> y;
	std::vector<double> z;
	int sizeVecticesVector = 0;

	std::vector<double> scalar;
	int sizeScalarVector = 0;

public:
	ScalarData();
	void setScalarValue(double x, double y, double z, double scalar);
	double getScalar(int index);
	double getX(int index);
	double getY(int index);
	double getZ(int index);
	int getSize();
	void printScalarField();
	void saveAsCSVfile(std::string path);

	virtual ~ScalarData();
};

#endif /* SCALARDATA_H_ */
