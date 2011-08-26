/*
 * Normalize.h
 *
 *  Created on: 12-06-2011
 *      Author: juanin
 */
#include "../AlgorithmStepHandler.h"

#ifndef NORMALIZESTEP
#define NORMALIZESTEP

class NormalizeStep: public AlgorithmStepHandler {
public:
	NormalizeStep();
	virtual ~NormalizeStep();

	void handleData(ParameterContainer *pc);
};

#endif
