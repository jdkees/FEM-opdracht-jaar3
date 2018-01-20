/*
 * DenseMatrix.cpp
 *
 *  Created on: Jul 5, 2017
 *      Author: majernik
 */

#include "DenseMatrix.h"
#include <iostream>

DenseMatrix::DenseMatrix()
{
	// TODO Auto-generated constructor stub

}

DenseMatrix::DenseMatrix(int i, int j)
{
	resize(i,j);
}

void DenseMatrix::resize(int i, int j)
{
	matrix.resize(i, j);
}

void DenseMatrix::setValue(double value, int i, int j)
{
	matrix.operator()(i-1, j-1) = value;
}

double DenseMatrix::getValue(int i, int j)
{
	return matrix.operator()(i-1, j-1);
}

int DenseMatrix::rows()
{
	return matrix.rows();
}

int DenseMatrix::columns()
{
	return matrix.cols();
}

void DenseMatrix::transpose()
{
	Eigen::MatrixXd m = matrix.transpose();
	matrix = m;
}

void DenseMatrix::conjugate()
{
	Eigen::MatrixXd m = matrix.conjugate();
	matrix = m;
}

void DenseMatrix::adjoint()
{

	Eigen::MatrixXd m = matrix.adjoint();
	matrix = m;

}

DenseMatrix DenseMatrix::inverse()
{
	DenseMatrix m;
	m.matrix = matrix.inverse();
	return m;
}

double DenseMatrix::determinant()
{
	return matrix.determinant();
}

void DenseMatrix::add(DenseMatrix m)
{
	matrix = matrix + m.matrix;
}

void DenseMatrix::substract(DenseMatrix m)
{
	matrix = matrix - m.matrix;
}

void DenseMatrix::multiply(DenseMatrix m)
{
	matrix = matrix * m.matrix;
}

void DenseMatrix::multiply(double d)
{
	matrix = d*matrix;
}


// ------------- Operator overloading. -----------------------------------
DenseMatrix DenseMatrix::operator+(const DenseMatrix& m2)
{
	DenseMatrix m;
	m.matrix = this->matrix + m2.matrix;

	return m;
}

DenseMatrix DenseMatrix::operator-(const DenseMatrix& m2)
{
	DenseMatrix m;
	m.matrix = this->matrix - m2.matrix;

	return m;
}

DenseMatrix DenseMatrix::operator*(const DenseMatrix& m2)
{
	DenseMatrix m;
	m.matrix = this->matrix * m2.matrix;

	return m;
}

DenseMatrix DenseMatrix::operator*(const double& d2)
{
	DenseMatrix m;
	m.matrix = d2 * this->matrix;

	return m;
}

double& DenseMatrix::operator() (unsigned int row, unsigned int col)
{
	return matrix.operator()(row-1, col-1);
}

double DenseMatrix::operator() (unsigned int row, unsigned int col) const
{
	return matrix.operator()(row-1, col-1);
}

void DenseMatrix::print()
{
	std::cout << matrix << std::endl;
}











DenseMatrix::~DenseMatrix()
{
	// TODO Auto-generated destructor stub
}


