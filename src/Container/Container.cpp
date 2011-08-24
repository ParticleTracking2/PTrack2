/*
 * Container.cpp
 *
 *  Created on: 12-06-2011
 *      Author: juanin
 */

#include "Container.h"

Container::Container() {
	// TODO Auto-generated constructor stub
}

Container::Container(void* data){
	mydata = data;
}

Container::Container(void** data){
	mydata2 = data;
}

Container::~Container() {
	// TODO Auto-generated destructor stub
	// Do Nothing
}

void Container::setData(void* data){
	mydata = data;
}

void Container::setData(void** data){
	mydata2 = data;
}

void* Container::getData(){
	return mydata;
}

void** Container::getData2(){
	return mydata2;
}
