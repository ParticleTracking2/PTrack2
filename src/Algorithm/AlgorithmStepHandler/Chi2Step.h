/*
 * Chi2.h
 *
 *  Created on: 12-06-2011
 *      Author: juanin
 */
#include "AlgorithmStepHandler.h"

#ifndef CHI2STEP
#define CHI2STEP

class Chi2Step : public AlgorithmStepHandler{
public:
	Chi2Step();
	virtual ~Chi2Step();

	static string name();
	void handleData();
};

#endif
