/*
 * AlgorithmStepHandler.cpp
 *
 *  Created on: 12-06-2011
 *      Author: juanin
 */

#include "AlgorithmStepHandler.h"

/**
 *******************************
 * Constructores y Destructores
 *******************************
 */
AlgorithmStepHandler::AlgorithmStepHandler(){
	this->next = 0;
}
/**
 *******************************
 * Metodos
 *******************************
 */
void AlgorithmStepHandler::setNext(AlgorithmStepHandler *nxt){
	next = nxt;
}
void AlgorithmStepHandler::nextStep(ParameterContainer *pc){
	if(next)
		next->handleData(pc);
}
void AlgorithmStepHandler::add(AlgorithmStepHandler *nxt){
	if(next)
		next->add(nxt);
	else
		next = nxt;
}

void AlgorithmStepHandler::handleData(ParameterContainer *pc){
	if(next)
		next->handleData(pc);
}

void AlgorithmStepHandler::printDescription(){
	cout << "::: No description available :::" << endl;
}
