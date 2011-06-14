/*
 * ParameterContainer.cpp
 *
 *  Created on: 12-06-2011
 *      Author: juanin
 */

#include "ParameterContainer.h"

ParameterContainer::ParameterContainer() {
	my_data.clear();
}

ParameterContainer::~ParameterContainer() {
	my_data.clear();
}

void ParameterContainer::addParam(string key, Container* data){
	my_data.insert(pair<string, Container*>(key,data));
}

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

void ParameterContainer::setParam(string key, Container* data){

}
