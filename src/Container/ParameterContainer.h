/*
 * ParameterContainer.h
 *
 *  Created on: 12-06-2011
 *      Author: juanin
 */
#include <map>
#include <string>
#include <vector>
#include "Container.h"
using namespace std;

#ifndef PARAMETERCONTAINER
#define PARAMETERCONTAINER

class ParameterContainer {
private:
	map<string, Container*> my_data;
	vector <string> keys;
public:
	ParameterContainer();
	virtual ~ParameterContainer();

	void addParam(string key, Container* data);
	void setParam(string key, Container* data);
	vector <string> getKeys();
	Container* popParam(string key);
	Container* getParam(string key);
	void* getData(string key);
	void** getData2(string key);
};

#endif
