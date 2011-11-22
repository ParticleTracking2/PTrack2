/*
 * Chi2HDCudaAlgorithm.cpp
 *
 *  Created on: 15-11-2011
 *      Author: ptrack
 */

#include "Chi2HDCudaAlgorithm.h"

vector<MyPeak> Chi2HDCudaAlgorithm::run(ParameterContainer *pc){
	MyLogger::log()->notice("[Chi2Algorithm] Running Chi2HD CUDA Algorithm");

	float d = 9.87;
	if(pc->existParam("-d"))
		d = (float)pc->getParamAsDouble("-d");

	float w = 1.84;
	if(pc->existParam("-w"))
		w = (float)pc->getParamAsDouble("-w");

	unsigned int ss = 2*floor(d/2 + 4*w/2)-1;
	unsigned int os = (ss-1)/2;

	MyLogger::log()->info("[Chi2HDAlgorithm] ***************************** ");
	MyLogger::log()->info("[Chi2HDAlgorithm] >> Initializing Device Data ");
	cuMyArray2D mydata = Chi2LibCuda::initializeData(data);
	MyLogger::log()->info("[Chi2HDAlgorithm] ***************************** ");
	MyLogger::log()->info("[Chi2HDAlgorithm] >> Normalize image ");
	Chi2LibCuda::normalizeImage(&mydata);

	MyLogger::log()->info("[Chi2HDAlgorithm] ***************************** ");
	MyLogger::log()->info("[Chi2HDAlgorithm] >> Generate Chi2 image ");
	cuMyArray2D mykernel = Chi2LibCuda::generateKernel(ss,os,d,w);
	cuMyArray2D chi_img = CHI2HD_createArray(mydata._sizeX+mykernel._sizeX-1, mydata._sizeY+mykernel._sizeY-1);
	Chi2LibCudaFFT::getChiImage(&mykernel, &mydata, &chi_img);

	//*******************************************
	CHI2HD_destroyArray(&mydata);
	CHI2HD_destroyArray(&mykernel);
	MyLogger::log()->notice("[Chi2Algorithm] cuMyArray2D Destroyed");

	vector<MyPeak> ret;
	return ret;
}
