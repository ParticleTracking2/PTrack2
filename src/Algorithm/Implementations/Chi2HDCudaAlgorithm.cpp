/*
 * Chi2HDCudaAlgorithm.cpp
 *
 *  Created on: 15-11-2011
 *      Author: ptrack
 */

#include "Chi2HDCudaAlgorithm.h"

vector<MyPeak> Chi2HDCudaAlgorithm::run(ParameterContainer *pc){
	MyLogger::log()->notice("[Chi2Algorithm] Running Chi2HD CUDA Algorithm");

	MyLogger::log()->notice("[Chi2Algorithm] Creating cuMyArray2D");
	cuMyArray2D tmp = CHI2HD_createArray(data->sX(), data->sY());
	MyLogger::log()->notice("[Chi2Algorithm] Creating cuMyArray2D: Created");
	CHI2HD_reset(&tmp,0);
	tmp._host_array = data->getCopy();
	CHI2HD_copyToDevice(&tmp);
	MyLogger::log()->notice("[Chi2Algorithm] Data copied to Device. Data[0]=%f", tmp._host_array[0]);
	//*******************************************

	myPair mm = CHI2HD_minMax(&tmp);
	MyLogger::log()->notice("[Chi2Algorithm] Min Max Found: Min=%f; Max=%f;", mm.first, mm.second);
	CHI2HD_normalize(&tmp, mm.first, mm.second);
	MyLogger::log()->notice("[Chi2Algorithm] Normalized");
	CHI2HD_copyToHost(&tmp);
	MyLogger::log()->notice("[Chi2Algorithm] Normalized. Data[0]=%f", tmp._host_array[0]);

	//*******************************************
	CHI2HD_destroyArray(&tmp);
	MyLogger::log()->notice("[Chi2Algorithm] cuMyArray2D Destroyed");

	vector<MyPeak> ret;
	return ret;
}
