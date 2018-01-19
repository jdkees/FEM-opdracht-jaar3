/*
 * GeoData.h
 *
 *  Created on: Jul 4, 2017
 *      Author: majernik
 *
 * This class is the datatype for holding and manipulating 3D-data.
 *
 */

#ifndef GEODATA_H_
#define GEODATA_H_
#include <vector>

class GeoData {
private:
	struct geodata
	{
		std::vector<double> x;
		std::vector<double> y;
		std::vector<double> z;
		int sizeVecticesVector = 0;

		std::vector<std::vector<int> > faces;
		int sizeFacesVector = 0;


	} geoData;

public:
	GeoData();
	void addVertex(double x, double y, double z);
	void addFace(std::vector<int> face);

	double* getX(int i);
	double* getY(int i);
	double* getZ(int i);
	std::vector<int>* getFace(int i);

	int verticesSize();
	int facesSize();

	void printGeoData();

	virtual ~GeoData();
};

#endif /* GEODATA_H_ */
