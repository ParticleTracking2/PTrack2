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

	MyLogger::log()->info("[Chi2HDCudaAlgorithm] ***************************** ");
	MyLogger::log()->info("[Chi2HDCudaAlgorithm] >> Generate Auxiliary Matrix ");
	MyLogger::log()->debug("[Chi2HDCudaAlgorithm] >> Allocating %ix%i", data->sX(), data->sY());
	cuMyMatrix grid_x(data->sX(), data->sY());
	cuMyMatrix grid_y(data->sX(), data->sY());
	cuMyMatrixi over(data->sX(), data->sY());
	MyLogger::log()->debug("[Chi2HDCudaAlgorithm] >> Allocation Complete ");
	Chi2LibCuda::generateGrid(&peaks, os, &grid_x, &grid_y, &over);
//	FileUtils::writeToFileM(&grid_x, "cugrid_x.txt");
//	FileUtils::writeToFileM(&grid_y, "cugrid_y.txt");
//	FileUtils::writeToFileM(&over, "cuover.txt");

	MyLogger::log()->info("[Chi2HDCudaAlgorithm] ***************************** ");
	MyLogger::log()->info("[Chi2HDCudaAlgorithm] >> Compute Chi2 Difference ");
	cuMyMatrix chi2diff(data->sX(), data->sY());
	float currentChi2Error = Chi2LibCuda::computeDifference(&cuImg, &grid_x, &grid_y, d, w, &chi2diff);
//	FileUtils::writeToFileM(&chi2diff, "cuchi2diff.txt");

	//*******************************************
	// Falta sumar el error Chi2
	//*******************************************

	MyLogger::log()->info("[Chi2HDCudaAlgorithm] ***************************** ");
	MyLogger::log()->info("[Chi2HDCudaAlgorithm] >> Add missed points ");
	unsigned int chi_cut = 2;
	if(pc->existParam("-chicut"))
		chi_cut = pc->getParamAsInt("-chicut");
	unsigned int total_found = 0;
	cuMyMatrix normaldata_chi(data->sX(), data->sY());

	unsigned int _maxIterations = 10, iterations = 0;
	while(iterations <= _maxIterations){
		MyLogger::log()->info("[Chi2HDCudaAlgorithm] >> Generating Scaled Image ");
		Chi2LibCudaHighDensity::generateScaledImage(&chi2diff, &normaldata_chi);
//		FileUtils::writeToFileM(&normaldata_chi, "cunormaldata_chi.txt");

		MyLogger::log()->info("[Chi2HDCudaAlgorithm] >> Obtaining new CHi2 Image ");
		Chi2LibCudaFFT::getChiImage(&cuKernel, &normaldata_chi, &cu_chi_img);
		FileUtils::writeToFileM(&cu_chi_img, "cu_chi_img2.txt");
		//*******************************************
		// No se si esta muy bien la convolucion
		// Puede ser problemas de presicion como siempre
		//*******************************************

		//*******************************************
		// Hasta Aquí OK
		//*******************************************

		break;
//
//		MyLogger::log()->info("[Chi2HDCudaAlgorithm] >> Obtaining new Peaks ");
//		vector<MyPeak> new_peaks = Chi2Lib::getPeaks(&chi_img, chi_cut, mindistance, minsep, use_threads); // ~7 Milisegundos
//
//		unsigned int old_size = peaks.size();
//		MyLogger::log()->info("[Chi2HDCudaAlgorithm] >> Checking inside image peaks ");
//		unsigned int found = Chi2LibHighDensity::checkInsidePeaks(&peaks, &new_peaks, data, os); // 0 Milisegundos
//		total_found += found;
//
//		if(found <= 0)
//			break;
//
//		MyLogger::log()->info("[Chi2HDCudaAlgorithm] >> Generating Auxiliary Matrix ");
//		Chi2Lib::generateGrid(&peaks,os, data, &grid_x, &grid_y, &over, use_threads); // ~200 Milisegundos
//
//		MyLogger::log()->info("[Chi2HDCudaAlgorithm] >> Computing Chi2 Difference ");
//		currentChi2Error = Chi2Lib::computeDifference(data, &grid_x, &grid_y, d, w, &chi2diff, use_threads); // ~80 Milisegundos
//
//		MyLogger::log()->info("[Chi2HDAlgorithm] >> Original No of Points: %i, +%i; Total Found = %i", old_size, found, total_found);

		iterations++;
	}
	//*******************************************
	// Prueba de los resulados hasta aquí
	//*******************************************


	vector<MyPeak> ret = Chi2LibCuda::convert(&peaks);
	Chi2LibCuda::translatePeaks(&ret, os);
	return ret;
}
