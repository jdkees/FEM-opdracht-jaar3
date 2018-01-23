/*
 * FEMelement.h
 *
 *  Created on: Jul 5, 2017
 *      Author: majernik
 *
 * This class hold all the data of one element. Most functions are getters and
 * setter functions. After the constructor is called, one can add the
 * element specific matrices.
 */

#ifndef FEMELEMENT_H_
#define FEMELEMENT_H_
#include "DenseMatrix.h"
#include "GeoData.h"
#include <vector>
#include <string>


class FEMelement
{

private:
	std::vector<DenseMatrix> elementMatrices;
	std::vector<std::string> labelElementMatrices;
	DenseMatrix normal;
	int facenumber;
	double area;
	bool boundryElement = true;

	std::vector<double*> x;
	std::vector<double*> y;
	std::vector<double*> z;

	std::vector<int> vertexNumbers;

public:
	FEMelement();
	FEMelement(int facenumber, bool boundry);

	void addElementMatrix(DenseMatrix m, std::string label = "");
	void setNormal(DenseMatrix normal);
	void setFacenumber(int n);
	void setArea(double area);
	void setBoundary(bool boundry);
	void addVertex(int vertexNo, double* x, double* y, double* z);

	DenseMatrix* 	 	getElementMatrix(std::string label);
	DenseMatrix* 	 	getElementMatrix(int id);
	DenseMatrix* 	 	getNormal();
	int					getLabelIndex(std::string label);
	std::string			getLabelName(int index);
	int				 	getFacenumber();
	double				getArea();
	int					getNumberOfMatrices();
	bool				isBoundaryElement();
	double				getX(int index);
	double				getY(int index);
	double				getZ(int index);
	std::vector<int>*   getVertexNumbers();

	virtual ~FEMelement();
};

#endif /* FEMELEMENT_H_ */
