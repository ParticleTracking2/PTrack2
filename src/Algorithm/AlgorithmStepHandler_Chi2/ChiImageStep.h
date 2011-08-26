/*
 * ChiImageStep.h
 *
 *  Created on: 26/08/2011
 *      Author: juanin
 */
#include "../AlgorithmStepHandler.h"

#ifndef CHIIMAGESTEP
#define CHIIMAGESTEP

class ChiImageStep: public AlgorithmStepHandler {
public:
	ChiImageStep();
	virtual ~ChiImageStep();

	void handleData(ParameterContainer *pc);
};

#endif
