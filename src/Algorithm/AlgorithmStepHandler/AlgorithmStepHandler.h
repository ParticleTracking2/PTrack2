/*
 * AlgorithmStepHandler.h
 *
 *  Created on: 12-06-2011
 *      Author: juanin
 */
#include <iostream>
#include <string>
using namespace std;

#ifndef ALGORITHMSTEPHANDLER
#define ALGORITHMSTEPHANDLER

class AlgorithmStepHandler {
protected:
	AlgorithmStepHandler *next;
public:
	static string name();
	AlgorithmStepHandler();
	virtual ~AlgorithmStepHandler(){}

	void setNext(AlgorithmStepHandler *nxt);
	void add(AlgorithmStepHandler *nxt);
	virtual void handleData();
};

#endif
