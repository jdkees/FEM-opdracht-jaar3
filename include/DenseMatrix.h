/*
 * DenseMatrix.h
 *
 *  Created on: Jul 5, 2017
 *      Author: majernik
 *
 * This class forms as an wrapper for the Eigen/Dense matrix datatype.
 * This class form the fundamental of the library.
 */

#ifndef DENSEMATRIX_H_
#define DENSEMATRIX_H_

#include <Eigen/Dense>


class DenseMatrix
{

private:
	// Variables for determining the position when using the << and comma operator
	// when filling the matrix.
	int opColumns = 1;
	int opRows = 1;

public:
	Eigen::MatrixXd matrix;

	DenseMatrix();
	DenseMatrix(int i, int j);

	void resize(int i, int j);
	void setValue(double value, int i, int j);
	double getValue(int i,  int j);
	int rows();
	int columns();

	// Matrix manipulation.
	void transpose();
	void conjugate();
	void adjoint();
	DenseMatrix inverse();
	double determinant();
	void add(DenseMatrix m);
	void substract(DenseMatrix m);
	void multiply(DenseMatrix m);
	void multiply(double d);

	DenseMatrix operator+(const DenseMatrix& m2);
	DenseMatrix operator-(const DenseMatrix& m2);
	DenseMatrix operator*(const DenseMatrix& m2);
	DenseMatrix operator*(const double& d2);

	double& operator() (unsigned int row, unsigned int col);
	double operator() (unsigned int row, unsigned int col) const;
	void print();

	virtual ~DenseMatrix();
};

#endif /* DENSEMATRIX_H_ */
