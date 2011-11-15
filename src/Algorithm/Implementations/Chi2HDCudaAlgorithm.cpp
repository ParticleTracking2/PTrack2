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
	cuMyArray2D tmp = CHI2HD_createArray(1024, 1024);
	MyLogger::log()->notice("[Chi2Algorithm] Creating cuMyArray2D: Created");
	CHI2HD_reset(&tmp, 10);
	MyLogger::log()->notice("[Chi2Algorithm] Default numbers = 10");
//	CHI2HD_copyToHost(&tmp);
//	MyLogger::log()->notice("[Chi2Algorithm] Copied to Host");
//	MyLogger::log()->notice("[Chi2Algorithm] Checking[0]=%f", tmp._host_array[0]);
	CHI2HD_squareIt(&tmp);
	MyLogger::log()->notice("[Chi2Algorithm] Squared");
//	CHI2HD_copyToHost(&tmp);
//	MyLogger::log()->notice("[Chi2Algorithm] Copied to Host");
//	MyLogger::log()->notice("[Chi2Algorithm] Checking[0]=%f", tmp._host_array[0]);
	CHI2HD_cubeIt(&tmp);
	MyLogger::log()->notice("[Chi2Algorithm] Cubed");
	CHI2HD_copyToHost(&tmp);
	MyLogger::log()->notice("[Chi2Algorithm] Copied to Host");
	MyLogger::log()->notice("[Chi2Algorithm] Checking[0]=%f", tmp._host_array[0]);
	CHI2HD_destroyArray(&tmp);
	MyLogger::log()->notice("[Chi2Algorithm] cuMyArray2D Destroyed");

	vector<MyPeak> ret;
	return ret;
}
