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
	MyLogger::log()->notice("[Chi2Algorithm] Data copied to Device");
	myPair mm = CHI2HD_minMax(&tmp);
	MyLogger::log()->notice("[Chi2Algorithm] Min Max Found: Min=%f; Max=%f;", mm._min, mm._max);
	CHI2HD_copyToHost(&tmp);
	MyLogger::log()->notice("[Chi2Algorithm] Copied to Host");
	float mymin = tmp._host_array[0];
	float mymax = tmp._host_array[0];
	for(unsigned int i=0; i < tmp.getSize(); ++i){
		if(tmp._host_array[i] < mymin)
			mymin = tmp._host_array[i];
		if(tmp._host_array[i] > mymax)
			mymax = tmp._host_array[i];
	}
	MyLogger::log()->notice("[Chi2Algorithm] Min Max Found: Min=%f; Max=%f;", mymin, mymax);
	CHI2HD_destroyArray(&tmp);
	MyLogger::log()->notice("[Chi2Algorithm] cuMyArray2D Destroyed");

	vector<MyPeak> ret;
	return ret;
}
