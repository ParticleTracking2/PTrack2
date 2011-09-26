/*
 * ChiDifferenceStep.h
 *
 *  Created on: 26/09/2011
 *      Author: ptrack
 */
#include "../AlgorithmStepHandler.h"
#include "math.h"

#ifndef CHIDIFFERENCESTEP
#define CHIDIFFERENCESTEP

class ChiDifferenceStep: public AlgorithmStepHandler {
public:
	void handleData(ParameterContainer *pc);
};

#endif /* CHIDIFFERENCESTEP */
