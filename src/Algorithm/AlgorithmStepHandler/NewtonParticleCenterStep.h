/*
 * NewtonParticleCenterStep.h
 *
 *  Created on: 12-06-2011
 *      Author: juanin
 */

#include "AlgorithmStepHandler.h"

#ifndef NEWTONPARTICLECENTERSTEP
#define NEWTONPARTICLECENTERSTEP

class NewtonParticleCenterStep: public AlgorithmStepHandler {
public:
	NewtonParticleCenterStep();
	virtual ~NewtonParticleCenterStep();

	static string name();
	void handleData();
};

#endif
