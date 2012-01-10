/*Factory
 * AlgorithmFactory.cpp
 *
 *  Created on: 11/10/2011
 *      Author: juanin
 */

#include "AlgorithmExecutor.h"

/**
 *******************************
 * Constructores y Destructores
 *******************************
 */
AlgorithmExecutor::AlgorithmExecutor(){
	selected = 0;
}

AlgorithmExecutor::AlgorithmExecutor(AlgorithmType type){
	selected = 0;
	select(type);
}

AlgorithmExecutor::~AlgorithmExecutor(){
	if(selected != 0)
		delete selected;
}

/**
 *******************************
 * Metodos
 *******************************
 */

vector<ArgObj> AlgorithmExecutor::getAllArguments(){
	vector<ArgObj> ret;
	ret.push_back(Chi2Algorithm::myArgs());
	ret.push_back(Chi2HDAlgorithm::myArgs());
	ret.push_back(Chi2HDCudaAlgorithm::myArgs());

	return ret;
}


AlgorithmType AlgorithmExecutor::translate(string alg){
	MyLogger::log()->debug("[AlgorithmExecutor][translate] Translating string Algorithm type: %s", alg.c_str());
	AlgorithmType ret = None_Algorithm;

	if(alg.compare("chi2")==0){
		MyLogger::log()->debug("[AlgorithmExecutor][translate] Translated to: Chi2_Algorithm");
		ret = Chi2_Algorithm;
	}
	if(alg.compare("chi2hd")==0){
		MyLogger::log()->debug("[AlgorithmExecutor][translate] Translated to: Chi2HD_Algorithm");
		ret = Chi2HD_Algorithm;
	}
	if(alg.compare("chi2hdcuda")==0){
		MyLogger::log()->debug("[AlgorithmExecutor][translate] Translated to: Chi2HDCuda_Algorithm");
		ret = Chi2HDCuda_Algorithm;
	}

	return ret;
}

void AlgorithmExecutor::select(AlgorithmType type){
	if(selected != 0)
		delete selected;

	switch (type) {
		case Chi2_Algorithm:
			MyLogger::log()->info("[AlgorithmExecutor][select] Chi2 Algorithm selected");
			selected = new Chi2Algorithm();
			break;
		case Chi2HD_Algorithm:
			MyLogger::log()->info("[AlgorithmExecutor][select] Chi2 High Density Algorithm selected");
			selected = new Chi2HDAlgorithm();
			break;
		case Chi2HDCuda_Algorithm:
			MyLogger::log()->info("[AlgorithmExecutor][select] Chi2 High Density CUDA Algorithm selected");
			selected = new Chi2HDCudaAlgorithm();
			break;
		case None_Algorithm:
			MyLogger::log()->info("[AlgorithmExecutor][select] No Algorithm selected");
			selected = new Algorithm();
			break;
	}
}

void AlgorithmExecutor::setParams(ParameterContainer *pc){
	selected->setData(pc);
}

void AlgorithmExecutor::setThreads(bool use_threads){
	selected->use_threads = use_threads;
}

vector<MyPeak> AlgorithmExecutor::execute(){
	return selected->run();
}
