/*
 * FEMobject.cpp
 *
 *  Created on: Jan 13, 2018
 *      Author: majernik
 */

#include "FEMobject.h"

FEMobject::FEMobject()
{

}

void FEMobject::setObjectData(GeoData * geodata, elementType elmType, int objectDimensions)
{
	this->geodata = geodata;
	this->elmType = elmType;
	this->objectDimensions = objectDimensions;

	// Set the nodesPerElement and DoF variables.
	switch(elmType)
	{
	case elementType::LINEAR:
		nodesPerElement = 2;
		degreesOfFreedom = objectDimensions;
		break;

	case elementType::TRIANGLES:			// < --- These values might be incorrect.
		nodesPerElement = 3;
		degreesOfFreedom = objectDimensions;
		break;

	};

	// Start parsing and creating element out of the GeoData.
	std::cout << ">> Creating elements and calculating its area and normal."<< std::endl;
	std::cout << "Progress: 00.0%"<< std::flush;
	int vertexNumber;
	for(int i = 0; i < geodata->facesSize(); i++)
	{
		FEMelement * elm = new FEMelement;
		elm->setFacenumber(i);
		calculateNormalandArea(i);
		elm->setNormal(tempNormal);
		elm->setArea(tempArea);
		elm->setBoundary(isBoundaryElement(i));

		for(int j = 0; j < geodata->getFace(i)->size(); j++)
		{
			vertexNumber = geodata->getFace(i)->at(j) - 1;
			elm->addVertex(vertexNumber, geodata->getX(vertexNumber), geodata->getY(vertexNumber), geodata->getZ(vertexNumber));
		}
		elmVector.push_back(elm);

		std::cout << "\r"<< std::flush;
		std::cout << "                  "<< std::flush;
		std::cout << "\r"<< std::flush;
		std::cout << "Progress: " << (double(i+1)/geodata->facesSize())*100 << "%" << std::flush;
	}
	std::cout <<std::endl;
	std::cout << ">> Completed creating elements."<< std::endl;
}

FEMobject::FEMobject(GeoData* geodata, elementType elmType,
		int objectDimensions) : geodata(geodata), elmType(elmType), objectDimensions(objectDimensions)
{
	// Set the nodesPerElement and DoF variables.
	switch(elmType)
	{
	case elementType::LINEAR:
		nodesPerElement = 2;
		degreesOfFreedom = objectDimensions;
		break;

	case elementType::TRIANGLES:			// < --- These values might be incorrect.
		nodesPerElement = 3;
		degreesOfFreedom = objectDimensions;
		break;

	};

	// Start parsing and creating element out of the GeoData.
	int vertexNumber;
	for(int i = 0; i < geodata->facesSize(); i++)
	{
		FEMelement * elm = new FEMelement;
		elm->setFacenumber(i);
		calculateNormalandArea(i);
		elm->setNormal(tempNormal);
		elm->setArea(tempArea);
		elm->setBoundary(isBoundaryElement(i));

		for(int j = 0; j < geodata->getFace(i)->size(); j++)
		{
			vertexNumber = geodata->getFace(i)->at(j) - 1;
			elm->addVertex(vertexNumber, geodata->getX(vertexNumber), geodata->getY(vertexNumber), geodata->getZ(vertexNumber));
		}

		elmVector.push_back(elm);
	}
}

// === >>>>>>> Public functions.  <<<<<< ===
FEMelement * FEMobject::element(int index)
{
	return elmVector.at(index);
}

void FEMobject::pushBackMatrixToAllElements(DenseMatrix m, std::string str)
{
	for(int i = 0; i < elmVector.size(); i++)
	{
		element(i)->addElementMatrix(m, str);
	}
}

void FEMobject::addGlobalMatrix(int rows, int columns, std::string str)
{
	SparseMatrix *m = new SparseMatrix(rows, columns);
	globalVec.push_back(m);
	globalNamesVec.push_back(str);
}

SparseMatrix* FEMobject::global(std::string label)
{
	for(int i = 0; i < globalNamesVec.size(); i++)
	{
		if(globalNamesVec.at(i) == label)
		{
 			return globalVec.at(i);
		}
	}
}

SparseMatrix* FEMobject::global(int index)
{
	return globalVec.at(index);
}

int FEMobject::getNumberOfElements()
{
	return elmVector.size();
}

void FEMobject::assemble(std::string strGlobal, std::string elementsName)
{
	FEMelementcontainer * elmCont = new FEMelementcontainer(&elmVector, elementsName);
	SparseMatrix* glob = global(strGlobal);
	std::vector<int>* vertexNumbers;

	double elMatrixColumns = elmCont->matrixAt(0)->columns();
	double elMatrixRows = elmCont->matrixAt(0)->rows();
	double globElementValue = 0;

	//std::cout<< "kut: " << glob->matrix <<std::endl;

	// Stiffness matrix assembly.
	if(elMatrixColumns > 1)
	{
		// Iterate through all the found element matrices with the given label.
		for(int nElement = 0; nElement < elmCont->numberOfFoundElements(); nElement++)
		{
			DenseMatrix * m = elmCont->matrixAt(nElement);
			vertexNumbers = elmCont->at(nElement)->getVertexNumbers();


			// Iterate through the matrix rows and columns.
			for(int j = 1; j < elMatrixColumns+1; j++)
			{
				for(int i = 1; i < elMatrixRows+1; i++)
				{
					// Get value in global matrix and ass element value.
					globElementValue = glob->getValue(vertexNumbers->at(i-1)+1, vertexNumbers->at(j-1)+1);
					globElementValue = globElementValue + m->getValue(i, j);

					glob->setValue(globElementValue,
							vertexNumbers->at(i-1)+1,
							vertexNumbers->at(j-1)+1);
				}
			}








		}
	}
	// Force matrix assembly.
	else
	{
		for(int nElement = 0; nElement < elmCont->numberOfFoundElements(); nElement++)
		{
			DenseMatrix * m = elmCont->matrixAt(nElement);
			vertexNumbers = elmCont->at(nElement)->getVertexNumbers();

			// Iterate through the matrix rows and columns.
			for(int i = 1; i < elMatrixRows+1; i++)
			{
				// Get value in global matrix and ass element value.
				globElementValue = glob->getValue(vertexNumbers->at(i-1)+1, 1);
				globElementValue = globElementValue + m->getValue(i, 1);

				glob->setValue(globElementValue,
						vertexNumbers->at(i-1)+1,
						1);
			}
		}
	}



	glob->surpressNonzeros(0,0);
}



// === >>>>>>> Helper functions.  <<<<<< ===
void FEMobject::calculateNormalandArea(int facenumber)
{

	if(elmType == elementType::TRIANGLES)
	{
		int p1 = geodata->getFace(facenumber)->at(0) - 1;
		int p2 = geodata->getFace(facenumber)->at(1) - 1;
		int p3 = geodata->getFace(facenumber)->at(2) - 1;

		double Vx = *geodata->getX(p2) - *geodata->getX(p1);
		double Vy = *geodata->getY(p2) - *geodata->getY(p1);
		double Vz = *geodata->getZ(p2) - *geodata->getZ(p1);

		double Wx = *geodata->getX(p3) - *geodata->getX(p1);
		double Wy = *geodata->getY(p3) - *geodata->getY(p1);
		double Wz = *geodata->getZ(p3) - *geodata->getZ(p1);

		double Nx = Vy*Wz - Vz*Wy;
		double Ny = Vz*Wx - Vx*Wz;
		double Nz = Vx*Wy - Vy*Wx;


		DenseMatrix normal(3,1);
		normal.setValue((Nx), 1,1);
		normal.setValue((Ny), 2,1);
		normal.setValue((Nz), 3,1);

		tempNormal = normal;
		tempArea = 0.5*sqrt(Nx*Nx + Ny*Ny + Nz*Nz);


	}

	else if(elmType == elementType::LINEAR)
	{

		int p1 = geodata->getFace(facenumber)->at(0) - 1;
		int p2 = geodata->getFace(facenumber)->at(1) - 1;

		double Vx = *geodata->getX(p2) - *geodata->getX(p1);
		double Vy = *geodata->getY(p2) - *geodata->getY(p1);
		double Vz = *geodata->getZ(p2) - *geodata->getZ(p1);


		DenseMatrix normal(3,1);
		normal.setValue((Vx), 1,1);
		normal.setValue((Vy), 2,1);
		normal.setValue((Vz), 3,1);

		tempNormal = normal;
		tempArea = 0;
	}
}

bool FEMobject::isBoundaryElement(int facenumber)
{
// Complex edge detection implementation here. Needs to be implemented.
		return false;
}


