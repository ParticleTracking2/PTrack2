/*
 * Algorithm.h
 *
 *  Created on: 12-06-2011
 *      Author: juanin
 */
#include "AlgorithmStepHandler.h"

#include "../ArgsProcessor.h"
#include "../Container/ParameterContainer.h"
#include "../Container/Container.h"

#include <iostream>
#include <string>
using namespace std;

#ifndef ALGORITHM
#define ALGORITHM

class Algorithm {
public:
	virtual ~Algorithm(){ }

	virtual void run();
	virtual void setInitialValues(ParameterContainer *pc);
};

#endif
