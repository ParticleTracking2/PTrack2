/*
 * FFTWStep.h
 *
 *  Created on: 13-06-2011
 *      Author: juanin
 */
#include "AlgorithmStepHandler.h"

#ifndef FFTWSTEP
#define FFTWSTEP

class FFTWStep: public AlgorithmStepHandler {
public:
	FFTWStep();
	virtual ~FFTWStep();

	static string name();
	void handleData();
};

#endif
