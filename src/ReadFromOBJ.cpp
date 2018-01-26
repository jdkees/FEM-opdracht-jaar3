/*
 * ReadFromOBJ.cpp
 *
 *  Created on: Jul 4, 2017
 *      Author: majernik
 */

#include "ReadFromOBJ.h"
#include <fstream>
#include <stdexcept>
#include <cstdlib>
#include <vector>
#include <iostream>

ReadFromOBJ::ReadFromOBJ()
{
	// TODO Auto-generated constructor stub

}

ReadFromOBJ::ReadFromOBJ(std::string path)
{
	setFilepath(path);
}


void ReadFromOBJ::setFilepath(std::string path)
{
	filepath = path;
}

void ReadFromOBJ::parse()
{
	std::cout<< ">> Start parsing: \"" << filepath << "\"." << std::endl;

	std::ifstream file(filepath.c_str());
	std::string str;

	if(file.is_open())
	{
		while(std::getline(file, str))
		{
			if(str.find("v") != std::string::npos)
			{
				processVertex(str);
			}

			if(str.find("f") != std::string::npos)
			{
				processFace(str);
			}
		}
	}
	else
	{
		throw std::runtime_error("Can not open file "+filepath+" or does not exist.");
	}

	std::cout<< ">> Completed parsing: \"" << filepath << "\"." << std::endl;
}

void ReadFromOBJ::processVertex(std::string str)
{
    std::string s = str;
    std::string delim = " ";

    s.erase(0, 2);

    std::size_t start = 0U;
    std::size_t end = s.find(delim);
    std::string::size_type sz;     // alias of size_t

    double x, y, z;



    if (end != std::string::npos)
    {

        x = std::stod(s.substr(start, end - start), &sz);
        start = end + delim.length();
        end = s.find(delim, start);

        y = std::stod(s.substr(start, end - start), &sz);
        start = end + delim.length();
        end = s.find(delim, start);

        if(end == std::string::npos)
        {
        	z = std::stod(s.substr(start, end), &sz);
        }else
        {
            z = std::stod(s.substr(start, end - start), &sz);
            start = end + delim.length();
            end = s.find(delim, start);
        }
    }

    addVertex(x, y, z);

}

void ReadFromOBJ::processFace(std::string str)
{
    std::string s = str;
    std::string delim = " ";

    s.erase(0, 2);

    std::size_t start = 0U;
    std::size_t end = s.find(delim);
    std::string::size_type sz;     // alias of size_t

    std::vector<int> face;


    while (end != std::string::npos)
    {
        face.push_back( std::stoi(s.substr(start, end - start), &sz) );
        start = end + delim.length();
        end = s.find(delim, start);
    }
    face.push_back( std::stoi(s.substr(start, end), &sz)  );


    addFace(face);

}

ReadFromOBJ::~ReadFromOBJ()
{
	// TODO Auto-generated destructor stub
}
