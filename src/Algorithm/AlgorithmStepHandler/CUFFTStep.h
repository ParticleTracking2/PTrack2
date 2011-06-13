/*
 * CUFFTStep.h
 *
 *  Created on: 13-06-2011
 *      Author: juanin
 */
#include "AlgorithmStepHandler.h"

#ifndef CUFFTSTEP
#define CUFFTSTEP

class CUFFTStep: public AlgorithmStepHandler {
public:
	CUFFTStep();
	virtual ~CUFFTStep();

	static string name();
	void handleData();
};

#endif
