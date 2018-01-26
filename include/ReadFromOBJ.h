/*
 * ReadFromOBJ.h
 *
 *  Created on: Jul 4, 2017
 *      Author: majernik
 *
 * This class reads a obj-file. The first argument of the constructor is the path
 * to the file. After the path to the file is set, then the function parse() needs
 * to be called.
 */

#ifndef READFROMOBJ_H_
#define READFROMOBJ_H_
#include "GeoData.h"
#include <string>
#include <iostream>

class ReadFromOBJ: public GeoData
{
private:
	std::string filepath;

	void processVertex(std::string str);
	void processFace(std::string str);
public:
	ReadFromOBJ();
	ReadFromOBJ(std::string path);

	void setFilepath(std::string path);
	void parse();

	virtual ~ReadFromOBJ();
};

#endif /* READFROMOBJ_H_ */
