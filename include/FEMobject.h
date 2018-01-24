/*
 * FEMobject.h
 *
 *  Created on: Jan 13, 2018
 *      Author: majernik
 *
 * This class is the center of the entire library.
 * The GeoData is fed into the class's constructor and parsed into elements.
 * Of each element the normal and area are calculated.
 * One type of matrix can be added to all the elements or a single matrix can
 * be added to a single element.
 * Afterwards one can perform assembly of the global matrices.
 *
 */

#ifndef FEMOBJECT_H_
#define FEMOBJECT_H_

#include "GeoData.h"
#include "FEMelement.h"
#include "DenseMatrix.h"
#include "SparseMatrix.h"
#include "FEMelementcontainer.h"
#include <vector>
#include <string>
#include <iostream>

enum elementType{LINEAR, TRIANGLES};

class FEMobject {
private:
	// Element properties.
	GeoData * geodata = nullptr;
	elementType elmType;
	int objectDimensions;
	int degreesOfFreedom;
	int nodesPerElement;
	std::vector<FEMelement*> elmVector;

	// Global matrix.
	std::vector<SparseMatrix*> globalVec;
	std::vector<std::string>  globalNamesVec;


public:
	// Element manipulation functions.
	FEMobject();
	FEMobject(GeoData * geodata, elementType elmType, int objectDimensions);
	void setObjectData(GeoData * geodata, elementType elmType, int objectDimensions);
	FEMelement * element(int index);
	void pushBackMatrixToAllElements(DenseMatrix m, std::string str);
	int getNumberOfElements();

	// Global manipulation functions.
	void addGlobalMatrix(int rows, int columns, std::string str);
	SparseMatrix* global(std::string label);
	SparseMatrix* global(int index);
	void assemble(std::string strGlobal, std::string elementsName);

// Helper functions and variables.
private:
	// Temps.
	DenseMatrix tempNormal;
	double tempArea;
	std::vector<int> tempDoF;

	void calculateNormalandArea(int facenumber);
	bool isBoundaryElement(int facenumber);
	void DoF(FEMelement* elm);
};

#endif /* FEMOBJECT_H_ */
