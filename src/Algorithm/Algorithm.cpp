/*
 * Algorithm.cpp
 *
 *  Created on: 12-06-2011
 *      Author: juanin
 */

#include "Algorithm.h"
#include <iostream>
#include <string>
using namespace std;

string Algorithm::name(){
	return "Generic Algorithm";
}

void Algorithm::run(){
	cout << name() << "::Running Algorithm" << endl;
}

void Algorithm::setInitialValues(ParameterContainer *pc){
	cout << name() << "::Setting Values" << endl;
}
