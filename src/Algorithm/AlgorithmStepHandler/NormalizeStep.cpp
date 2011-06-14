/*
 * Normalize.cpp
 *
 *  Created on: 12-06-2011
 *      Author: juanin
 */

#include "NormalizeStep.h"

NormalizeStep::NormalizeStep() {
	// TODO Auto-generated constructor stub

}

NormalizeStep::~NormalizeStep() {
	// TODO Auto-generated destructor stub
}

string NormalizeStep::name(){
	return "Normalize Step";
}

void NormalizeStep::handleData(){
	cout << name() << " Data" << endl;
	if(next)
		next->handleData();
}
