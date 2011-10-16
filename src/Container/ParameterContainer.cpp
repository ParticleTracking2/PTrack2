/*
 * ParameterContainer.cpp
 *
 *  Created on: 12-06-2011
 *      Author: juanin
 */

#include "ParameterContainer.h"

/**
 *******************************
 * Constructores y Destructores
 *******************************
 */
ParameterContainer::ParameterContainer() {
	my_data.clear();
}

ParameterContainer::~ParameterContainer() {
	my_data.clear();
}

/**
 *******************************
 * Metodos
 *******************************
 */
void ParameterContainer::addParam(string key, Container* data){
	my_data.insert(pair<string, Container*>(key,data));
}

void ParameterContainer::addParam(string key, Container* data, string description){
	data->setDescription(description);
	my_data.insert(pair<string, Container*>(key,data));
}

void ParameterContainer::setParam(string key, Container* data){
	Container *pop;
	if(existParam(key)){
		pop = popParam(key);
		data->setDescription(pop->getDescription());
		delete pop;
		addParam(key,data);
	}
}

void ParameterContainer::setParam(string key, Container* data, string description){
	Container *pop;
	if(existParam(key)){
		pop = popParam(key);
		data->setDescription(description);
		delete pop;
		addParam(key,data);
	}
}

/**
 *******************************
 * Funciones
 *******************************
 */
Container* ParameterContainer::popParam(string key){
	map<string, Container*>::const_iterator iter;
	iter = my_data.find(key);
	if(iter != my_data.end()){
		my_data.erase(key);
		return iter->second;
	}else
		return NULL;
}

Container* ParameterContainer::getParam(string key){
	map<string, Container*>::const_iterator iter;
	iter = my_data.find(key);
	if(iter != my_data.end())
		return iter->second;
	else
		return NULL;
}

int ParameterContainer::getParamAsInt(string key){
	map<string, Container*>::const_iterator iter;
	iter = my_data.find(key);
	if(iter != my_data.end())
		return iter->second->getDataInt();
	else
		return 0;
}

double ParameterContainer::getParamAsDouble(string key){
	map<string, Container*>::const_iterator iter;
	iter = my_data.find(key);
	if(iter != my_data.end())
		return iter->second->getDataDouble();
	else
		return 0;
}

string ParameterContainer::getParamAsString(string key){
	map<string, Container*>::const_iterator iter;
	iter = my_data.find(key);
	if(iter != my_data.end())
		return iter->second->getDataString();
	else
		return 0;
}

bool ParameterContainer::existParam(string key){
	map<string, Container*>::const_iterator iter;
	iter = my_data.find(key);
	if(iter != my_data.end())
		return true;
	else
		return false;
}

vector <string> ParameterContainer::getKeys(){
	vector<string> my_keys;
	map<string, Container*>::iterator it;
	for(it = my_data.begin(); it != my_data.end(); ++it){
		my_keys.push_back(it->first);
	}
	return my_keys;
}

void* ParameterContainer::getData(string key){
	if(getParam(key))
		return getParam(key)->getData();
	else
		return NULL;
}

void** ParameterContainer::getData2(string key){
	if(getParam(key))
		return getParam(key)->getData2();
	else
		return NULL;
}

void ParameterContainer::printInformation(){
	cout << "**********************************" << endl;
	cout << "ParameterContainer Information:" << endl;
	map<string, Container*>::iterator it;
	for(it = my_data.begin(); it != my_data.end(); ++it){
		cout << "Key: " << "'" << it->first << "'\t\t";
		//cout << " Type: " << "'" << typeid(getData(keys[i])).name() << "'\t\t";
		cout << " Description: " << "'" << it->second->getDescription() << "'" << endl;
	}
	cout << "**********************************" << endl;
}
