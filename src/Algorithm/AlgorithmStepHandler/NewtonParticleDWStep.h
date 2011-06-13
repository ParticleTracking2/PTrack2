/*
 * NewtonParticleDWStep.h
 *
 *  Created on: 12-06-2011
 *      Author: juanin
 */
#include "AlgorithmStepHandler.h"

#ifndef NEWTONPARTICLEDWSTEP
#define NEWTONPARTICLEDWSTEP

class NewtonParticleDWStep: public AlgorithmStepHandler {
public:
	NewtonParticleDWStep();
	virtual ~NewtonParticleDWStep();

	static string name();
	void handleData();
};

#endif
