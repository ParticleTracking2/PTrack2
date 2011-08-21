/*
 * Normalize.cpp
 *
 *  Created on: 12-06-2011
 *      Author: juanin
 */

#include "NormalizeStep.h"

string NormalizeStep::name(){
	return "Normalize Step";
}
/**
 *******************************
 * Constructores y Destructores
 *******************************
 */
NormalizeStep::NormalizeStep() {
	// TODO Auto-generated constructor stub

}

NormalizeStep::~NormalizeStep() {
	// TODO Auto-generated destructor stub
}

/**
 *******************************
 * Metodos
 *******************************
 */
void NormalizeStep::handleData(){
	cout << name() << " Data" << endl;
	if(next)
		next->handleData();
}
