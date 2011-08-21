/*
 * NewtonParticleDWStep.cpp
 *
 *  Created on: 12-06-2011
 *      Author: juanin
 */

#include "NewtonParticleDWStep.h"

string NewtonParticleDWStep::name(){
	return "NewtonParticleDW Step";
}
/**
 *******************************
 * Constructores y Destructores
 *******************************
 */
NewtonParticleDWStep::NewtonParticleDWStep() {
	// TODO Auto-generated constructor stub
}

NewtonParticleDWStep::~NewtonParticleDWStep() {
	// TODO Auto-generated destructor stub
}

/**
 *******************************
 * Metodos
 *******************************
 */
void NewtonParticleDWStep::handleData(){
	cout << name() << " Data" << endl;
	if(next)
		next->handleData();
}
