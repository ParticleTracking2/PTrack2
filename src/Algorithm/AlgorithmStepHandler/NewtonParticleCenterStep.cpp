/*
 * NewtonParticleCenterStep.cpp
 *
 *  Created on: 12-06-2011
 *      Author: juanin
 */

#include "NewtonParticleCenterStep.h"

string NewtonParticleCenterStep::name(){
	return "NewtonParticleCenter Step";
}
/**
 *******************************
 * Constructores y Destructores
 *******************************
 */
NewtonParticleCenterStep::NewtonParticleCenterStep() {
	// TODO Auto-generated constructor stub
}

NewtonParticleCenterStep::~NewtonParticleCenterStep() {
	// TODO Auto-generated destructor stub
}

/**
 *******************************
 * Metodos
 *******************************
 */
void NewtonParticleCenterStep::handleData(){
	cout << name() << " Data" << endl;
	if(next)
		next->handleData();
}
