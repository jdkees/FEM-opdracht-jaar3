/*
 * SparseMatrix.h
 *
 *  Created on: Jul 8, 2017
 *      Author: majernik
 *
 * This class forms as an wrapper for the Eigen/Sparse matrix datatype.
 * This class form the fundamental of the library.
 */

#ifndef SPARSEMATRIX_H_
#define SPARSEMATRIX_H_
#include <Eigen/SparseCore>
#include <Eigen/Sparse>
//#include <vector>

enum sparseSolvers {CHOLESKY};

class SparseMatrix
{
private:

public:
	Eigen::SparseMatrix<double> matrix;

	SparseMatrix();
	SparseMatrix(int i, int j);
	void setSize(int i, int j);
	void setValue(double v, int i, int j);
	double getValue(int i, int j);
	int rows();
	int columns();
	void surpressNonzeros(double reference, double tolerance);

	// Matrix manipulation.
	void transpose();
	void adjoint();
	void add(SparseMatrix m);
	void substract(SparseMatrix m);
	void multiply(SparseMatrix m);
	void multiply(double d);
	void crossOut(int i, int j);
	void swapRow(int row1, int row2);
	void swapColumns(int col1, int col2);
	SparseMatrix solve(SparseMatrix* B, sparseSolvers type);

	// Operator overloading.
	SparseMatrix operator+(const SparseMatrix& m2);
	SparseMatrix operator*(const SparseMatrix& m2);

	virtual ~SparseMatrix();
};

#endif /* SPARSEMATRIX_H_ */
