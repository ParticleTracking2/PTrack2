/*
 * ChiDifferenceStep.h
 *
 *  Created on: 12-06-2011
 *      Author: juanin
 */
#include "AlgorithmStepHandler.h"

#ifndef CHIDIFFERENCESTEP
#define CHIDIFFERENCESTEP

class ChiDifferenceStep: public AlgorithmStepHandler {
public:
	ChiDifferenceStep();
	virtual ~ChiDifferenceStep();

	static string name();
	void handleData();
};

#endif
