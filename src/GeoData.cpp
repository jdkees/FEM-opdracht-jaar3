/*
 * GeoData.cpp
 *
 *  Created on: Jul 4, 2017
 *      Author: majernik
 */

#include "GeoData.h"
#include <iostream>

GeoData::GeoData() {
	// TODO Auto-generated constructor stub

}

void GeoData::addVertex(double x, double y, double z)
{
	geoData.x.push_back(x);
	geoData.y.push_back(y);
	geoData.z.push_back(z);

	geoData.sizeVecticesVector++;

}

void GeoData::addFace(std::vector<int> face)
{
	geoData.faces.push_back(face);

	geoData.sizeFacesVector++;
}

double* GeoData::getX(int i)
{
	return &geoData.x.at(i);
}

double* GeoData::getY(int i)
{
	return &geoData.y.at(i);
}

double* GeoData::getZ(int i)
{
	return &geoData.z.at(i);
}

std::vector<int>* GeoData::getFace(int i)
{
	return &geoData.faces.at(i);
}

int GeoData::verticesSize()
{
	return geoData.sizeVecticesVector;
}

int GeoData::facesSize()
{
	return geoData.sizeFacesVector;
}

void GeoData::printGeoData()
{
	std::cout << ">>> Printing geometry data." <<std::endl;
	std::cout << "Number of vertices: " << verticesSize() << std::endl;
	std::cout << "Number of faces:    " << facesSize() << std::endl;

	for(int i = 0; i < verticesSize(); i++)
	{
		std::cout << geoData.x.at(i) << " " << geoData.y.at(i) << " " << geoData.z.at(i) << std::endl;

	}

	for(int i = 0; i < facesSize(); i++)
	{
		std::cout << "Face: " << i << " vertex no.: ";

		for(int j = 0; j < geoData.faces.at(i).size(); j++)
		{
			std::cout << geoData.faces.at(i).at(j) << " ";
		}

		std:: cout << std::endl;
	}
}



GeoData::~GeoData() {
	// TODO Auto-generated destructor stub
}

