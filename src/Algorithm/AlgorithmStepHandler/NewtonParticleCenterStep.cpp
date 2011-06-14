/*
 * NewtonParticleCenterStep.cpp
 *
 *  Created on: 12-06-2011
 *      Author: juanin
 */

#include "NewtonParticleCenterStep.h"

NewtonParticleCenterStep::NewtonParticleCenterStep() {
	// TODO Auto-generated constructor stub

}

NewtonParticleCenterStep::~NewtonParticleCenterStep() {
	// TODO Auto-generated destructor stub
}

string NewtonParticleCenterStep::name(){
	return "NewtonParticleCenter Step";
}

void NewtonParticleCenterStep::handleData(){
	cout << name() << " Data" << endl;
	if(next)
		next->handleData();
}
