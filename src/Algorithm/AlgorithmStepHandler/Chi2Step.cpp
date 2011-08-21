/*
 * Chi2.cpp
 *
 *  Created on: 12-06-2011
 *      Author: juanin
 */

#include "Chi2Step.h"

string Chi2Step::name(){
	return "Chi2 Step";
}
/**
 *******************************
 * Constructores y Destructores
 *******************************
 */
Chi2Step::Chi2Step() {
	cout << "Constructing " << name() << endl;
}

Chi2Step::~Chi2Step() {
	// TODO Auto-generated destructor stub
}

/**
 *******************************
 * Metodos
 *******************************
 */
void Chi2Step::handleData(){
	cout << name() << " Data" << endl;
	if(next)
		next->handleData();
}
