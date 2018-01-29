/*
 * PythonPlot.h
 *
 *  Created on: Jan 28, 2018
 *      Author: majernik
 */

#ifndef PYTHONPLOT_H_
#define PYTHONPLOT_H_
#include <Python.h>
#include <string>
#include <iostream>
#include <stdexcept>


class PythonPlot
{
private:
	PyObject* PyString;
	PyObject* PyModule;
	PyObject* PyFunction;
	PyObject* PyArgTuple;
	PyObject* PyReturn;
	int nArgs = 0;

	std::string path;
	std::string functionName;
	std::string fileName;

public:
	PythonPlot();
	virtual ~PythonPlot();

	void setPath(std::string path, std::string fileName);
	void selectFuntionByName(std::string functionName, int numberOfArguments);
	void appendArgument(PyObject* arg);
	void callFunction();
};

#endif /* PYTHONPLOT_H_ */
