/*
 * AlgorithmStepHandler.h
 *
 *  Created on: 12-06-2011
 *      Author: juanin
 */
#include <iostream>
#include <cmath>
#include "../Container/ParameterContainer.h"
#include "../Container/Container.h"
#include "../Image/MyImage.h"
using namespace std;

#ifndef ALGORITHMSTEPHANDLER
#define ALGORITHMSTEPHANDLER

class AlgorithmStepHandler {
protected:
	AlgorithmStepHandler *next;
public:
	AlgorithmStepHandler();
	virtual ~AlgorithmStepHandler(){}

	void setNext(AlgorithmStepHandler *nxt);
	void add(AlgorithmStepHandler *nxt);
	virtual void handleData(ParameterContainer *pc);
};

#endif
