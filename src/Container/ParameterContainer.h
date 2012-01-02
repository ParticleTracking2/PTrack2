/*
 * ParameterContainer.h
 *
 *  Created on: 12-06-2011
 *      Author: juanin
 */
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <typeinfo>
#include "Container.h"
using namespace std;

#ifndef PARAMETERCONTAINER
#define PARAMETERCONTAINER

/**
 * Clase contenedora de parametros.
 * La implementacion se realiza con un Map de una llave como String y su valor como Un contenedor de datos de distintos tipos.
 */
class ParameterContainer {
private:
	map<string, Container*> my_data;
public:
	ParameterContainer();
	virtual ~ParameterContainer();

	void addParam(string key, Container* data);
	void addParam(string key, Container* data, string description);
	void setParam(string key, Container* data);
	void setParam(string key, Container* data, string description);
	vector <string> getKeys();
	Container* popParam(string key);
	Container* getParam(string key);

	int getParamAsInt(string key);
	double getParamAsDouble(string key);
	string getParamAsString(string key);

	bool existParam(string key);

	void* getData(string key);
	void** getData2(string key);

	void printInformation();
};

#endif
