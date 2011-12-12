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

	int ss = 2*floor(d/2 + 4*w/2)-1;
	int os = (ss-1)/2;

	MyLogger::log()->info("[Chi2HDCudaAlgorithm] ***************************** ");
	MyLogger::log()->info("[Chi2HDCudaAlgorithm] >> Initializing Device Data ");
	cuMyMatrix cuImg = Chi2LibCuda::initializeData(data);

	MyLogger::log()->info("[Chi2HDCudaAlgorithm] ***************************** ");
	MyLogger::log()->info("[Chi2HDCudaAlgorithm] >> Normalize image ");
	Chi2LibCuda::normalizeImage(&cuImg);
	Chi2Lib::normalizeImage(data);

	MyLogger::log()->info("[Chi2HDCudaAlgorithm] ***************************** ");
	MyLogger::log()->info("[Chi2HDCudaAlgorithm] >> Generate Chi2 image ");
	cuMyMatrix cuKernel = Chi2LibCuda::generateKernel(ss,os,d,w);
	cuMyMatrix cu_chi_img(cuImg.sizeX()+cuKernel.sizeX()-1, cuImg.sizeY()+cuKernel.sizeY()-1);
	Chi2LibCudaFFT::getChiImage(&cuKernel, &cuImg, &cu_chi_img);

	MyLogger::log()->info("[Chi2HDCudaAlgorithm] ***************************** ");
	MyLogger::log()->info("[Chi2HDCudaAlgorithm] >> Obtain peaks of Chi2 Image ");
	unsigned int threshold = 5, minsep = 1, mindistance = 5;
	cuMyPeakArray peaks = Chi2LibCuda::getPeaks(&cu_chi_img, threshold, mindistance, minsep);

//	MyLogger::log()->info("[Chi2HDCudaAlgorithm] ***************************** ");
//	MyLogger::log()->info("[Chi2HDCudaAlgorithm] >> Generate Auxiliary Matrix ");
//	MyLogger::log()->debug("[Chi2HDCudaAlgorithm] >> Allocating %ix%i", data->sX(), data->sY());
//	cuMyMatrix grid_x(data->sX(), data->sY());
//	cuMyMatrix grid_y(data->sX(), data->sY());
//	cuMyMatrixi over(data->sX(), data->sY());
//	MyLogger::log()->debug("[Chi2HDAlgorithm] >> Allocation Complete ");
//	Chi2LibCuda::generateGrid(&peaks, os, &cuImg, &grid_x, &grid_y, &over);
//
//	FileUtils::writeToFileM(&grid_x, "cugrid_x.txt");
//	FileUtils::writeToFileM(&grid_y, "cugrid_y.txt");
//	FileUtils::writeToFileM(&over, "cuover.txt");
	//*******************************************
	// Prueba de los resulados hasta aquí
	//*******************************************

	vector<MyPeak> ret = Chi2LibCuda::convert(&peaks);
	Chi2LibCuda::translatePeaks(&ret, os);
	return ret;
}
