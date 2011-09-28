/*
 * AlgorithmStepHandler.h
 *
 *  Created on: 12-06-2011
 *      Author: juanin
 */
#include <iostream>
#include <cmath>
#include <fstream>
#include "../Container/ParameterContainer.h"
#include "../Container/Container.h"
#include "../Image/MyImage.h"
#include "../MyUtils.h"
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
	void nextStep(ParameterContainer *pc);
	void add(AlgorithmStepHandler *nxt);
	virtual void handleData(ParameterContainer *pc);
	virtual void printDescription();
};

#endif
