/*
 * CheckParticlesStep.h
 *
 *  Created on: 02/10/2011
 *      Author: juanin
 */
#include "../AlgorithmStepHandler.h"

#ifndef CHECKPARTICLESSTEP
#define CHECKPARTICLESSTEP

class CheckParticlesStep: public AlgorithmStepHandler {
public:
	void handleData(ParameterContainer *pc);
	void printDescription();
};

#endif
