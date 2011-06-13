/*
 * particleGridStep.h
 *
 *  Created on: 12-06-2011
 *      Author: juanin
 */
#include "AlgorithmStepHandler.h"

#ifndef PARTICLEGRIDSTEP
#define PARTICLEGRIDSTEP

class ParticleGridStep: public AlgorithmStepHandler {
public:
	ParticleGridStep();
	virtual ~ParticleGridStep();

	static string name();
		void handleData();
};

#endif
