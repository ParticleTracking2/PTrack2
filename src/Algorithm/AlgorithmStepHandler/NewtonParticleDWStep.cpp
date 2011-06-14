/*
 * NewtonParticleDWStep.cpp
 *
 *  Created on: 12-06-2011
 *      Author: juanin
 */

#include "NewtonParticleDWStep.h"

NewtonParticleDWStep::NewtonParticleDWStep() {
	// TODO Auto-generated constructor stub

}

NewtonParticleDWStep::~NewtonParticleDWStep() {
	// TODO Auto-generated destructor stub
}

string NewtonParticleDWStep::name(){
	return "NewtonParticleDW Step";
}

void NewtonParticleDWStep::handleData(){
	cout << name() << " Data" << endl;
	if(next)
		next->handleData();
}
