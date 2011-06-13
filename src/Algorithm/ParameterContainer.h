/*
 * ParameterContainer.h
 *
 *  Created on: 12-06-2011
 *      Author: juanin
 */
#include <map>
#include <string>
#include "Container.h"
using namespace std;

#ifndef PARAMETERCONTAINER
#define PARAMETERCONTAINER

class ParameterContainer {
	map<string, Container*> my_data;
public:
	ParameterContainer();
	virtual ~ParameterContainer();

	void addParam(string key, Container* data);
	Container* popParam(string key);
	Container* getParam(string key);
	void setParam(string key, Container* data);
};

#endif
