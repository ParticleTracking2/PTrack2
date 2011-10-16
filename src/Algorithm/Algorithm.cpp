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
AlgorithmType Algorithm::translate(string alg){
	MyLogger::log()->debug("[Algorithm][translate] Translating string Algorithm type: %s", alg.c_str());
	AlgorithmType ret = None_Algorithm;

	if(alg.compare("chi2")==0){
		MyLogger::log()->debug("[Algorithm][translate] Translated to: Chi2_Algorithm");
		ret = Chi2_Algorithm;
	}
	if(alg.compare("chi2hd")==0){
		MyLogger::log()->debug("[Algorithm][translate] Translated to: Chi2HD_Algorithm");
		ret = Chi2HD_Algorithm;
	}

	return ret;
}

void Algorithm::setData(MyMatrix<double>* data){
	this->data = data;
}

vector<MyPeak> Algorithm::run(ParameterContainer *pc){
	MyLogger::log()->debug("[Algorithm][run] Running nothing, please implement this class function.");
	vector<MyPeak> ret;
	return ret;

}
