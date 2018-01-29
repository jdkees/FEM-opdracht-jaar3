/*
 * PythonPlot.cpp
 *
 *  Created on: Jan 28, 2018
 *      Author: majernik
 */

#include <PythonPlot.h>

PythonPlot::PythonPlot()
{
	// TODO Auto-generated constructor stub
	Py_Initialize();

//	PyRun_SimpleString("import sys");
//	PyRun_SimpleString("sys.path.append(\"/home/majernik/Programming/C++/FEM3/python\")");

//	PyString = PyString_FromString("plot");
//
//	PyModule = PyImport_Import(PyString);
//
//	PyFunction = PyObject_GetAttrString(PyModule, "kut");
//
//	PyObject_CallObject(PyFunction, NULL);


}

PythonPlot::~PythonPlot() {
	// TODO Auto-generated destructor stub
}

void PythonPlot::setPath(std::string path, std::string fileName)
{
	this->path = path;
	this->fileName = fileName;

	std::string cat = "sys.path.append(\""+ path +"\")";
	PyRun_SimpleString("import sys");
	PyRun_SimpleString(cat.c_str());


	PyString = PyString_FromString(fileName.c_str());

	PyModule = PyImport_Import(PyString);

}


void PythonPlot::selectFuntionByName(std::string functionName, int numberOfArguments)
{
	this->functionName = functionName;

	PyFunction = PyObject_GetAttrString(PyModule, functionName.c_str());

	if(numberOfArguments == 0)
	{
		PyArgTuple = NULL;
	}else
	{

		PyArgTuple = PyTuple_New(numberOfArguments);
	}

}

void PythonPlot::appendArgument(PyObject* arg)
{
	PyTuple_SetItem(PyArgTuple, nArgs, arg);

	nArgs++;
}



void PythonPlot::callFunction()
{
	std::cout << ">> Running Python: " << "\"" << fileName << "\"." << std::endl;
	std::cout << "   - Calling function: " << "\"" << functionName << "\"" << std::endl;
	std::cout << " ===================== WARNING! REPARE TO ENTER HELL! =====================" << std::endl;
	std::cout << " You will probably encounter a shitstorm of warnings and errors " << std::endl;
	std::cout << "from Python. You probably haven't sacrifices enough lambs or try newborns instead." << std::endl;
	std::cout << "In the best case scenario this will take some days. You can continue binge watching"<<std::endl;
	std::cout << "your favorite NetFlix series." <<std::endl;
	std::cout << " ===================== WARNING! REPARE TO ENTER HELL! =====================" << std::endl;

	PyReturn = PyObject_CallObject(PyFunction, PyArgTuple);

}
