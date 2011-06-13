/*
 * Chi2.cpp
 *
 *  Created on: 12-06-2011
 *      Author: juanin
 */

#include "Chi2Step.h"

Chi2Step::Chi2Step() {
	// TODO Auto-generated constructor stub

}

Chi2Step::~Chi2Step() {
	// TODO Auto-generated destructor stub
}

string Chi2Step::name(){
	return "Chi2 Step";
}

void Chi2Step::handleData(){
	cout << name() << " Data" << endl;
	next->handleData();
}
