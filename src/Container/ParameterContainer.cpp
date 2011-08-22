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
	keys.push_back(key);
}

void ParameterContainer::setParam(string key, Container* data){

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

vector <string> ParameterContainer::getKeys(){
	return keys;
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
