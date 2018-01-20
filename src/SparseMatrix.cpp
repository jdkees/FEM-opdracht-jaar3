/*
 * SparseMatrix.cpp
 *
 *  Created on: Jul 8, 2017
 *      Author: majernik
 */

#include "SparseMatrix.h"
#include <Eigen/Core>
#include <iostream>

SparseMatrix::SparseMatrix()
{
	// TODO Auto-generated constructor stub
}

SparseMatrix::SparseMatrix(int i, int j)
{
	setSize(i, j);
}

void SparseMatrix::setSize(int i, int j)
{
	matrix.resize(i,j);
}

void SparseMatrix::setValue(double v, int i, int j)
{
	matrix.coeffRef(i-1, j-1) = v;
}

void SparseMatrix::transpose()
{
	Eigen::SparseMatrix<double>  m = matrix.transpose();
	matrix = m;
}

void SparseMatrix::adjoint()
{
	Eigen::SparseMatrix<double> m = matrix.adjoint();
	matrix = m;
}

void SparseMatrix::add(SparseMatrix m)
{
	matrix = matrix + m.matrix;
}

void SparseMatrix::substract(SparseMatrix m)
{
	matrix = matrix - m.matrix;
}

void SparseMatrix::multiply(SparseMatrix m)
{
	matrix = matrix * m.matrix;
}

void SparseMatrix::multiply(double d)
{
	matrix = d * matrix;
}

double SparseMatrix::getValue(int i, int j)
{
	return matrix.coeff(i-1, j-1);
}

SparseMatrix SparseMatrix::solve(SparseMatrix* B,
		sparseSolvers type)
{
	if(type == CHOLESKY)
	{
		Eigen::SimplicialCholesky<Eigen::SparseMatrix<double> > chol(matrix);
		SparseMatrix x(B->rows(), 1);

		x.matrix = chol.solve(B->matrix);

		return x;
	}
}

int SparseMatrix::rows()
{
	return matrix.rows();
}

int SparseMatrix::columns()
{
	return matrix.cols();
}

void SparseMatrix::crossOut(int i, int j)
{

	// Zero out column.
	for (Eigen::SparseMatrix<double>::InnerIterator it(matrix, j-1); it; ++it)
	{
		setValue(0, it.row()+1,it.col()+1);
		setValue(0, it.col()+1,it.row()+1);
	}

	// Zero out row.
	for(int k = i; k <= columns(); k++)
	{
		setValue(0, k, j);
	}


	setValue(1.0, i,j); // << edit here.
	surpressNonzeros(0,0);

}

void SparseMatrix::swapRow(int row1, int row2)
{
	Eigen::PermutationMatrix<Eigen::Dynamic, Eigen::Dynamic> perm;
	perm.setIdentity(matrix.rows());

	perm.applyTranspositionOnTheLeft(row1-1, row2-1);

	matrix = perm*matrix;

}

void SparseMatrix::swapColumns(int col1, int col2)
{
	Eigen::PermutationMatrix<Eigen::Dynamic, Eigen::Dynamic> perm;
	perm.setIdentity(matrix.rows());

	perm.applyTranspositionOnTheLeft(col1-1, col2-1);

	matrix = matrix*perm;
}


void SparseMatrix::surpressNonzeros(double reference, double tolerance)
{
	matrix.prune(reference, tolerance);
}


SparseMatrix::~SparseMatrix()
{
	// TODO Auto-generated destructor stub
}

