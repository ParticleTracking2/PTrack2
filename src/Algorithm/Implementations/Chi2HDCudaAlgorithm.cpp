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
//		FileUtils::writeToFileM(&cu_chi_img, "cu_chi_img2.txt");

		MyLogger::log()->info("[Chi2HDCudaAlgorithm] >> Obtaining new Peaks ");
		cuMyPeakArray new_peaks = Chi2LibCuda::getPeaks(&cu_chi_img, chi_cut, mindistance, minsep);

		unsigned int old_size = peaks.size();
		MyLogger::log()->info("[Chi2HDCudaAlgorithm] >> Checking inside image peaks ");
		unsigned int found = Chi2LibCudaHighDensity::checkInsidePeaks(&peaks, &new_peaks, &cuImg, os);
		total_found += found;

		if(found <= 0)
			break;

		MyLogger::log()->info("[Chi2HDCudaAlgorithm] >> Generating Auxiliary Matrix ");
		Chi2LibCuda::generateGrid(&peaks, os, &grid_x, &grid_y, &over);

		MyLogger::log()->info("[Chi2HDCudaAlgorithm] >> Computing Chi2 Difference ");
		currentChi2Error = Chi2LibCuda::computeDifference(&cuImg, &grid_x, &grid_y, d, w, &chi2diff);

		MyLogger::log()->info("[Chi2HDAlgorithm] >> Original No of Points: %i, +%i; Total Found = %i", old_size, found, total_found);

		iterations++;
	}
	peaks.sortByChiIntensity();
	Chi2LibCudaFFTCache::eraseAll();

	MyLogger::log()->info("[Chi2HDCudaAlgorithm] ***************************** ");
	MyLogger::log()->info("[Chi2HDCudaAlgorithm] >> Recompute Auxiliary matrix and Chi2 Difference ");
	MyLogger::log()->debug("[Chi2HDCudaAlgorithm] >> Recompute Auxiliary matrix");
	Chi2LibCuda::generateGrid(&peaks, os, &grid_x, &grid_y, &over);

	MyLogger::log()->info("[Chi2HDCudaAlgorithm] >> Recompute Chi2 Difference");
	currentChi2Error = Chi2LibCuda::computeDifference(&cuImg, &grid_x, &grid_y, d, w, &chi2diff);

	MyLogger::log()->info("[Chi2HDCudaAlgorithm] ***************************** ");
	MyLogger::log()->info("[Chi2HDCudaAlgorithm] >> Minimizing Chi2 Error ");
	unsigned int _minChi2Delta = 1;
	iterations = 0;
	double chi2Delta = currentChi2Error;

	_maxIterations = 5;
	if(pc->existParam("-maxchi2miniter"))
		_maxIterations = pc->getParamAsInt("-maxchi2miniter");
	while( fabs(chi2Delta) > _minChi2Delta &&  iterations < _maxIterations){
		Chi2LibCuda::newtonCenter(&over, &chi2diff, &peaks, os, d, w, ss, 20.0);
		peaks.includeDeltas();

		Chi2LibCuda::generateGrid(&peaks, os, &grid_x, &grid_y, &over);
		chi2diff.reset(0);

		double newChi2Err = Chi2LibCuda::computeDifference(&cuImg, &grid_x, &grid_y, d, w, &chi2diff);
		MyLogger::log()->info("[Chi2HDAlgorithm] >> Chi2Error: %f", newChi2Err);
		chi2Delta = currentChi2Error - newChi2Err;
		currentChi2Error = currentChi2Error-chi2Delta;
		iterations++;
	}

	MyLogger::log()->info("[Chi2HDCudaAlgorithm] ***************************** ");
	MyLogger::log()->info("[Chi2HDCudaAlgorithm] >> Checking particles by pixel intensity and voronoi area Tom's algorithm ");

	MyLogger::log()->info("[Chi2HDCudaAlgorithm] >> Remove outside image peaks");
	Chi2LibCudaHighDensity::filterPeaksOutside(&peaks, &cuImg, os);

	MyLogger::log()->info("[Chi2HDCudaAlgorithm] >> Apply Gaussian Fit ");
	pair<double,double> mypair = Chi2LibCudaHighDensity::gaussianFit(&peaks,&cuImg, os);
	double mu = mypair.first;
	double sigma = mypair.second;
	MyLogger::log()->info("[Chi2HDCudaAlgorithm] >> Total peaks: %i; MU=%f; SIGMA=%f", peaks.size(), mu, sigma);

	MyLogger::log()->info("[Chi2HDCudaAlgorithm] ***************************** ");
	double par_thresh = mu-3.0*sigma;
	double vor_thresh = 50.0;
	if(pc->existParam("-vorcut"))
		vor_thresh = pc->getParamAsDouble("-vorcut");

	MyLogger::log()->info("[Chi2HDCudaAlgorithm] >> Filter 'Bad' Peaks using Voronoi Area: %f - Intensity: %f", vor_thresh, par_thresh);
	Chi2LibCudaHighDensity::removeBadPeaks(&peaks, &cuImg, vor_thresh, par_thresh, os);

	if(pc->existParam("-2filteri")){
		MyLogger::log()->info("[Chi2HDCudaAlgorithm] >> Second Filter 'Bad' Peaks using intensity");
		unsigned int old_total  = peaks.size();
		Chi2LibCudaHighDensity::removeBadIntensityPeaks(&peaks, &cuImg, pc->getParamAsDouble("-2filteri"), os);
		unsigned int new_total  = peaks.size();
		MyLogger::log()->info("[Chi2HDCudaAlgorithm] >> New Number of peaks: %i, Filtered :%i", new_total, (old_total - new_total));
	}

	if(pc->existParam("-2filterv")){
		MyLogger::log()->info("[Chi2HDCudaAlgorithm] >> Second Filter 'Bad' Peaks using Voronoi Area");
		unsigned int old_total  = peaks.size();
		Chi2LibCudaHighDensity::removeBadVoronoiPeaks(&peaks, &cuImg, pc->getParamAsDouble("-2filterv"), os);
		unsigned int new_total  = peaks.size();
		MyLogger::log()->info("[Chi2HDCudaAlgorithm] >> New Number of peaks: %i, Filtered :%i", new_total, (old_total - new_total));
	}

	MyLogger::log()->info("[Chi2HDCudaAlgorithm] ***************************** ");
	MyLogger::log()->info("[Chi2HDCudaAlgorithm] >> Recompute Auxiliary matrix and Chi2 Difference");
	MyLogger::log()->info("[Chi2HDCudaAlgorithm] >> Recompute Auxiliary matrix");
	Chi2LibCuda::generateGrid(&peaks, os, &grid_x, &grid_y, &over);
	MyLogger::log()->info("[Chi2HDCudaAlgorithm] >> Recompute Chi2 Difference");
	currentChi2Error = Chi2LibCuda::computeDifference(&cuImg, &grid_x, &grid_y, d, w, &chi2diff);
	chi2Delta = 1000000.0;
	iterations = 0;
	MyLogger::log()->info("[Chi2HDCudaAlgorithm] ***************************** ");
	MyLogger::log()->info("[Chi2HDCudaAlgorithm] >> Minimizing Chi2 Error ");
	while( fabs(chi2Delta) > _minChi2Delta &&  iterations < _maxIterations){
		Chi2LibCuda::newtonCenter(&over, &chi2diff, &peaks, os, d, w, ss, 20.0);
		peaks.includeDeltas();

		Chi2LibCuda::generateGrid(&peaks, os, &grid_x, &grid_y, &over);
		chi2diff.reset(0);

		double newChi2Err = Chi2LibCuda::computeDifference(&cuImg, &grid_x, &grid_y, d, w, &chi2diff);
		MyLogger::log()->info("[Chi2HDAlgorithm] >> Chi2Error: %f", newChi2Err);
		chi2Delta = currentChi2Error - newChi2Err;
		currentChi2Error = currentChi2Error-chi2Delta;
		iterations++;
	}

	MyLogger::log()->info("[Chi2HDCudaAlgorithm] ***************************** ");
	MyLogger::log()->info("[Chi2HDCudaAlgorithm] >> Recomputing Voronoi areas ");
	Chi2LibCudaQhull::addVoronoiAreas(&peaks);

	MyLogger::log()->info("[Chi2HDCudaAlgorithm] >> Translating coordenates ");
	Chi2LibCuda::translatePeaks(&peaks, os);

	float vor_areaSL = 75.0;
	if(pc->existParam("-vorsl"))
		vor_areaSL = (float)pc->getParamAsDouble("-vorsl");
	MyLogger::log()->info("[Chi2HDCudaAlgorithm] >> Adding State ");
	Chi2LibCuda::addState(&peaks, vor_areaSL);

	//*******************************************
	// Pruebas
	//*******************************************


	MyLogger::log()->info("[Chi2HDCudaAlgorithm] >> Converting Peaks to original vector ");
	vector<MyPeak> ret = Chi2LibCuda::convert(&peaks);
	return ret;
}
