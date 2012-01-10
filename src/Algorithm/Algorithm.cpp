/*
 * Algorithm.cpp
 *
 *  Created on: 12-06-2011
 *      Author: juanin
 */

#include "Algorithm.h"

/**
 *******************************
 * Constructores y Destructores
 *******************************
 */
Algorithm::Algorithm(){ }

Algorithm::~Algorithm(){ }

/**
 *******************************
 * Funciones
 *******************************
 */
ArgObj Algorithm::myArgs(){
	ArgObj ret;
	return ret;
}

void Algorithm::setData(ParameterContainer *pc){

}

vector<MyPeak> Algorithm::run(){
	MyLogger::log()->debug("[Algorithm][run] Running nothing, please implement this class function.");
	vector<MyPeak> ret;
	return ret;

}
