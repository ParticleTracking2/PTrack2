/*
 * AlgorithmStepHandler.cpp
 *
 *  Created on: 12-06-2011
 *      Author: juanin
 */

#include "AlgorithmStepHandler.h"

string AlgorithmStepHandler::name(){
	return "AlgorithmStepHandler";
}
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

void AlgorithmStepHandler::add(AlgorithmStepHandler *nxt){
	if(next)
		next->add(nxt);
	else
		next = nxt;
}

void AlgorithmStepHandler::handleData(){
	cout << name() << " Data" << endl;
	if(next)
		next->handleData();
}
