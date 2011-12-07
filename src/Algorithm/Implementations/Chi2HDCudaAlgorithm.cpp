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

	MyLogger::log()->info("[Chi2HDCudaAlgorithm] ***************************** ");
	MyLogger::log()->info("[Chi2HDCudaAlgorithm] >> Initializing Device Data ");
	cuMyArray2D cuImg = Chi2LibCuda::initializeData(data);

	MyLogger::log()->info("[Chi2HDCudaAlgorithm] ***************************** ");
	MyLogger::log()->info("[Chi2HDCudaAlgorithm] >> Normalize image ");
	Chi2LibCuda::normalizeImage(&cuImg);
	Chi2Lib::normalizeImage(data);

	MyLogger::log()->info("[Chi2HDCudaAlgorithm] ***************************** ");
	MyLogger::log()->info("[Chi2HDCudaAlgorithm] >> Generate Chi2 image ");
	cuMyArray2D cuKernel = Chi2LibCuda::generateKernel(ss,os,d,w);
	cuMyArray2D cu_chi_img = CHI2HD_createArray(cuImg._sizeX+cuKernel._sizeX-1, cuImg._sizeY+cuKernel._sizeY-1);
	Chi2LibCudaFFT::getChiImage(&cuKernel, &cuImg, &cu_chi_img);

	MyLogger::log()->info("[Chi2HDCudaAlgorithm] ***************************** ");
	MyLogger::log()->info("[Chi2HDCudaAlgorithm] >> Obtain peaks of Chi2 Image ");
	unsigned int threshold = 5, minsep = 1, mindistance = 5;
	cuPeakArray peaks = Chi2LibCuda::getPeaks(&cu_chi_img, threshold, mindistance, minsep);

	MyLogger::log()->info("[Chi2HDCudaAlgorithm] ***************************** ");
	MyLogger::log()->info("[Chi2HDCudaAlgorithm] >> Generate Auxiliary Matrix ");
	MyLogger::log()->debug("[Chi2HDCudaAlgorithm] >> Allocating %ix%i", data->sX(), data->sY());

	cuMyMatrix testData(cuImg._sizeX, cuImg._sizeY);

	//*******************************************
	// Prueba de los resulados hasta aquí
	//*******************************************
	CHI2HD_destroyArray(&cuImg);
	CHI2HD_destroyArray(&cuKernel);
	CHI2HD_destroyArray(&cu_chi_img);
	MyLogger::log()->notice("[Chi2HDCudaAlgorithm] cuMyArray2D Destroyed");

	vector<MyPeak> ret;
	return ret;
}
