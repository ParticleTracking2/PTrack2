/*
 * ReComputeGridAndDiff.h
 *
 *  Created on: 01/10/2011
 *      Author: juanin
 */
#include "../AlgorithmStepHandler.h"
#include "ParticleGridStep.h"
#include "ChiDifferenceStep.h"

#ifndef RECOMPUTEGRIDANDDIFF
#define RECOMPUTEGRIDANDDIFF

class ReComputeGridAndDiff: public AlgorithmStepHandler {
public:
	void handleData(ParameterContainer *pc);
	void printDescription();
};

#endif
