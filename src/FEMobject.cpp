/*
 * FEMobject.cpp
 *
 *  Created on: Jan 13, 2018
 *      Author: majernik
 */

#include "FEMobject.h"

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
		elm->setBoundry(isBoundryElement(i));

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

	double elMatrixColumns = elmCont->matrixAt(0)->columns();
	double elMatrixRows = elmCont->matrixAt(0)->rows();
	double globElementValue = 0;

	// Stiffness matrix assembly.
	if(elMatrixColumns > 1)
	{
		for(int nElement = 0; nElement < elmCont->numberOfFoundElements(); nElement++)
		{
			DoF(elmCont->at(nElement));

			for(int i = 0; i < tempDoF.size(); i++)
			{
				for(int j = 0; j < tempDoF.size(); j++)
				{
					globElementValue = glob->getValue(tempDoF.at(i), tempDoF.at(j));
					globElementValue += elmCont->matrixAt(nElement)->getValue(i+1, j+1);

					glob->setValue(globElementValue, tempDoF.at(i), tempDoF.at(j));
				}
			}
		}
	}

	// Force matrix assembly.
	else
	{
		for(int nElement = 0; nElement < elmCont->numberOfFoundElements(); nElement++)
		{
			DoF(elmCont->at(nElement));

			for(int i = 0; i < tempDoF.size(); i++)
			{
				globElementValue = glob->getValue(tempDoF.at(i), 1);
				globElementValue += elmCont->matrixAt(nElement)->getValue(i+1, 1);

				glob->setValue(globElementValue, tempDoF.at(i), 1);
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

bool FEMobject::isBoundryElement(int facenumber)
{
// Complex edge detection implementation here. Needs to be implemented.
		return false;
}

void FEMobject::DoF(FEMelement* elm)
{
	tempDoF.clear();
	//std::cout << "Element" <<std::endl;
	for(int i = 0; i < elm->getVertexNumbers()->size(); i++)
	{
		for(int q = degreesOfFreedom-1; q >= 0; q--)
		{
			//std::cout << "Node#:" <<  (elm->getVertexNumbers()->at(i)+1) << " q:" << q << " n:" << DegreesOfFreedom << " DoF#: " << (elm->getVertexNumbers()->at(i)+1) * DegreesOfFreedom - q << std::endl;
			tempDoF.push_back((elm->getVertexNumbers()->at(i)+1) * degreesOfFreedom - q);
		}
	}
}


