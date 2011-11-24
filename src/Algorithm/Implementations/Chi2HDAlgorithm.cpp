/*
 * Chi2Algorithm.cpp
 *
 *  Created on: 12-06-2011
 *      Author: juanin
 */

#include "Chi2HDAlgorithm.h"

vector<MyPeak> Chi2HDAlgorithm::run(ParameterContainer *pc){
	MyLogger::log()->notice("[Chi2HDAlgorithm] Running Chi2 High Density Algorithm");
	double d = 9.87;
	if(pc->existParam("-d"))
		d = pc->getParamAsDouble("-d");

	double w = 1.84;
	if(pc->existParam("-w"))
		w = pc->getParamAsDouble("-w");

	int ss = 2*floor(d/2 + 4*w/2)-1;
	int os = (ss-1)/2;

	MyLogger::log()->info("[Chi2HDAlgorithm] ***************************** ");
	MyLogger::log()->info("[Chi2HDAlgorithm] >> Normalize image ");
	FileUtils::writeToFileM(data, "img.txt");
	Chi2Lib::normalizeImage(data);
	FileUtils::writeToFileM(data, "img-normalized.txt");

	MyLogger::log()->info("[Chi2HDAlgorithm] ***************************** ");
	MyLogger::log()->info("[Chi2HDAlgorithm] >> Generate Chi2 image ");
	MyMatrix<double> kernel = Chi2Lib::generateKernel(ss,os,d,w);
	MyMatrix<double> chi_img(data->sX()+kernel.sX()-1, data->sY()+kernel.sY()-1);
	Chi2LibFFTW::getChiImage(&kernel, data, &chi_img, use_threads);	// ~430|560 -> |290 Milisegundos
	FileUtils::writeToFileM(&kernel, "kernel.txt");
	FileUtils::writeToFileM(&chi_img, "chi_img.txt");

	MyLogger::log()->info("[Chi2HDAlgorithm] ***************************** ");
	MyLogger::log()->info("[Chi2HDAlgorithm] >> Obtain peaks of Chi2 Image ");
	unsigned int threshold = 5, minsep = 1, mindistance = 5;
	vector<MyPeak> peaks = Chi2Lib::getPeaks(&chi_img, threshold, mindistance, minsep, use_threads); // ~120|150 -> |125 Milisegundos

	Chi2LibFFTWCache::dump();
//	return peaks;

	MyLogger::log()->info("[Chi2HDAlgorithm] ***************************** ");
	MyLogger::log()->info("[Chi2HDAlgorithm] >> Generate Auxiliary Matrix ");
	MyLogger::log()->debug("[Chi2HDAlgorithm] >> Allocating %ix%i", data->sX(), data->sY());
	MyMatrix<double> grid_x(data->sX(), data->sY());
	MyMatrix<double> grid_y(data->sX(), data->sY());
	MyMatrix<int> over(data->sX(), data->sY());
	MyLogger::log()->debug("[Chi2HDAlgorithm] >> Allocation Complete ");
	Chi2Lib::generateGrid(&peaks, os, data, &grid_x, &grid_y, &over, use_threads);	// ~170|200 -> |150 Milisegundos

	MyLogger::log()->info("[Chi2HDAlgorithm] ***************************** ");
	MyLogger::log()->info("[Chi2HDAlgorithm] >> Compute Chi2 Difference ");
	MyMatrix<double> chi2diff(data->sX(), data->sY());
	double currentChi2Error = Chi2Lib::computeDifference(data, &grid_x, &grid_y, d, w, &chi2diff, use_threads); // ~70|80 -> |50 Milisegundos

	MyLogger::log()->info("[Chi2HDAlgorithm] ***************************** ");
	MyLogger::log()->info("[Chi2HDAlgorithm] >> Add missed points ");
	unsigned int chi_cut = 2;
	if(pc->existParam("-chicut"))
		chi_cut = pc->getParamAsInt("-chicut");
	unsigned int total_found = 0;
	MyMatrix<double> normaldata_chi(data->sX(), data->sY()); // No necesita reset

	unsigned int _maxIterations = 10, iterations = 0;
	while(iterations <= _maxIterations){
		MyLogger::log()->info("[Chi2HDAlgorithm] >> Generating Scaled Image ");
		Chi2LibHighDensity::generateScaledImage(&chi2diff, &normaldata_chi); // ~ 15 Milisegundos

		MyLogger::log()->info("[Chi2HDAlgorithm] >> Obtaining new CHi2 Image ");
		Chi2LibFFTW::getChiImage(&kernel, &normaldata_chi, &chi_img, use_threads); // ~390|500 -> |220 Milisegundos

		MyLogger::log()->info("[Chi2HDAlgorithm] >> Obtaining new Peaks ");
		vector<MyPeak> new_peaks = Chi2Lib::getPeaks(&chi_img, chi_cut, mindistance, minsep, use_threads); // ~7 Milisegundos

		unsigned int old_size = peaks.size();
		MyLogger::log()->info("[Chi2HDAlgorithm] >> Checking inside image peaks ");
		unsigned int found = Chi2LibHighDensity::checkInsidePeaks(&peaks, &new_peaks, data, os); // 0 Milisegundos
		total_found += found;

		if(found <= 0)
			break;

		MyLogger::log()->info("[Chi2HDAlgorithm] >> Generating Auxiliary Matrix ");
		Chi2Lib::generateGrid(&peaks,os, data, &grid_x, &grid_y, &over, use_threads); // ~200 Milisegundos

		MyLogger::log()->info("[Chi2HDAlgorithm] >> Computing Chi2 Difference ");
		currentChi2Error = Chi2Lib::computeDifference(data, &grid_x, &grid_y, d, w, &chi2diff, use_threads); // ~80 Milisegundos

		MyLogger::log()->info("[Chi2HDAlgorithm] >> Original No of Points: %i, +%i; Total Found = %i", old_size, found, total_found);

		iterations++;
	}
	sort(peaks.begin(), peaks.end(), MyPeak::compareMe);
	Chi2LibFFTWCache::eraseAll();

	MyLogger::log()->info("[Chi2HDAlgorithm] ***************************** ");
	MyLogger::log()->info("[Chi2HDAlgorithm] >> Recompute Auxiliary matrix and Chi2 Difference");
	MyLogger::log()->info("[Chi2HDAlgorithm] >> Recompute Auxiliary matrix");
	Chi2Lib::generateGrid(&peaks,os, data, &grid_x, &grid_y, &over, use_threads);

	MyLogger::log()->info("[Chi2HDAlgorithm] >> Recompute Chi2 Difference");
	currentChi2Error = Chi2Lib::computeDifference(data, &grid_x, &grid_y, d, w, &chi2diff, use_threads);

	MyLogger::log()->info("[Chi2HDAlgorithm] ***************************** ");
	MyLogger::log()->info("[Chi2HDAlgorithm] >> Minimizing Chi2 Error ");
	unsigned int _minChi2Delta = 1;
	iterations = 0;
	double chi2Delta = currentChi2Error;

	_maxIterations = 5;
	if(pc->existParam("-maxchi2miniter"))
		_maxIterations = pc->getParamAsInt("-maxchi2miniter");
	while( fabs(chi2Delta) > _minChi2Delta &&  iterations < _maxIterations){
		Chi2Lib::newtonCenter(&over, &chi2diff, &peaks, os, d, w, ss, 20.0, use_threads); // ~400 -> ~250 Milisegundos

		for(unsigned int i=0; i < peaks.size(); ++i){
			peaks.at(i).px = peaks.at(i).px + peaks.at(i).dpx;
			peaks.at(i).py = peaks.at(i).py + peaks.at(i).dpy;

			peaks.at(i).x = (unsigned int)rint(peaks.at(i).px);
			peaks.at(i).y = (unsigned int)rint(peaks.at(i).py);
		}

		Chi2Lib::generateGrid(&peaks, os, data, &grid_x, &grid_y, &over, use_threads);
		chi2diff.reset(0);

		double newChi2Err = Chi2Lib::computeDifference(data, &grid_x, &grid_y, d, w, &chi2diff, use_threads);
		chi2Delta = currentChi2Error - newChi2Err;
		currentChi2Error = currentChi2Error-chi2Delta;
		iterations++;
	}

	MyLogger::log()->info("[Chi2HDAlgorithm] ***************************** ");
	MyLogger::log()->info("[Chi2HDAlgorithm] >> Checking particles by pixel intensity and voronoi area Tom's algorithm ");

	//for each valid point (inside) build the histogram
	//compute mu & sigma for the histogram
	MyLogger::log()->info("[Chi2HDAlgorithm] >> Remove outside image peaks");
	Chi2LibHighDensity::filterPeaksOutside(&peaks, data, os);

	MyLogger::log()->info("[Chi2HDAlgorithm] >> Apply Gaussian Fit ");
	pair<double,double> mypair = Chi2LibHighDensity::gaussianFit(&peaks, data, os);
	double mu = mypair.first;
	double sigma = mypair.second;
	MyLogger::log()->info("[Chi2HDAlgorithm] >> Total peaks: %i; MU=%f; SIGMA=%f", peaks.size(), mu, sigma);

	MyLogger::log()->info("[Chi2HDAlgorithm] ***************************** ");
	double par_thresh = mu-3.0*sigma;
	double vor_thresh = 50.0;
	if(pc->existParam("-vorcut"))
		vor_thresh = pc->getParamAsDouble("-vorcut");

	MyLogger::log()->info("[Chi2HDAlgorithm] >> Filter 'Bad' Peaks using Voronoi Area: %f - Intensity: %f", vor_thresh, par_thresh);
	Chi2LibHighDensity::removeBadPeaks(&peaks, data, vor_thresh, par_thresh, os);

	if(pc->existParam("-2filteri")){
		MyLogger::log()->info("[Chi2HDAlgorithm] >> Second Filter 'Bad' Peaks using intensity");
		unsigned int old_total  = peaks.size();
		Chi2LibHighDensity::removeBadIntensityPeaks(&peaks, data, pc->getParamAsDouble("-2filteri"), os);
		unsigned int new_total  = peaks.size();
		MyLogger::log()->info("[Chi2HDAlgorithm] >> New Number of peaks: %i, Filtered :%i", new_total, (old_total - new_total));
	}

	if(pc->existParam("-2filterv")){
		MyLogger::log()->info("[Chi2HDAlgorithm] >> Second Filter 'Bad' Peaks using Voronoi Area");
		unsigned int old_total  = peaks.size();
		Chi2LibHighDensity::removeBadVoronoiPeaks(&peaks, data, pc->getParamAsDouble("-2filterv"), os);
		unsigned int new_total  = peaks.size();
		MyLogger::log()->info("[Chi2HDAlgorithm] >> New Number of peaks: %i, Filtered :%i", new_total, (old_total - new_total));
	}

	MyLogger::log()->info("[Chi2HDAlgorithm] ***************************** ");
	MyLogger::log()->info("[Chi2HDAlgorithm] >> Recompute Auxiliary matrix and Chi2 Difference");
	MyLogger::log()->info("[Chi2HDAlgorithm] >> Recompute Auxiliary matrix");
	Chi2Lib::generateGrid(&peaks,os, data, &grid_x, &grid_y, &over, use_threads);
	MyLogger::log()->info("[Chi2HDAlgorithm] >> Recompute Chi2 Difference");
	Chi2Lib::computeDifference(data, &grid_x, &grid_y, d, w, &chi2diff, use_threads);
	chi2Delta = 1000000.0;
	iterations = 0;
	MyLogger::log()->info("[Chi2HDAlgorithm] ***************************** ");
	MyLogger::log()->info("[Chi2HDAlgorithm] >> Minimizing Chi2 Error ");

	while( fabs(chi2Delta) > _minChi2Delta &&  iterations < _maxIterations){
		Chi2Lib::newtonCenter(&over, &chi2diff, &peaks, os, d, w, ss, 20.0, use_threads);

		for(unsigned int i=0; i < peaks.size(); ++i){
			peaks.at(i).px = peaks.at(i).px + peaks.at(i).dpx;
			peaks.at(i).py = peaks.at(i).py + peaks.at(i).dpy;

			peaks.at(i).x = (unsigned int)rint(peaks.at(i).px);
			peaks.at(i).y = (unsigned int)rint(peaks.at(i).py);
		}

		Chi2Lib::generateGrid(&peaks, os, data, &grid_x, &grid_y, &over, use_threads);
		chi2diff.reset(0);

		double newChi2Err = Chi2Lib::computeDifference(data, &grid_x, &grid_y, d, w, &chi2diff, use_threads);
		chi2Delta = currentChi2Error - newChi2Err;
		currentChi2Error = currentChi2Error-chi2Delta;
		iterations++;
	}

	MyLogger::log()->info("[Chi2HDAlgorithm] ***************************** ");
	MyLogger::log()->info("[Chi2HDAlgorithm] >> Recomputing Voronoi areas ");
	Chi2LibQhull::addVoronoiAreas(&peaks);
	FileUtils::writeToFileM(&peaks, "peaks_post_add_voronoi_areas.txt");

	MyLogger::log()->info("[Chi2HDAlgorithm] >> Translating coordenates ");
	Chi2Lib::translatePeaks(&peaks, os);
	FileUtils::writeToFileM(&peaks, "peaks_post_translate.txt");

	double vor_areaSL = 75.0;
	if(pc->existParam("-vorsl"))
		vor_areaSL = pc->getParamAsDouble("-vorsl");
	MyLogger::log()->info("[Chi2HDAlgorithm] >> Adding State ");
	Chi2Lib::addState(&peaks, vor_areaSL);

	return peaks;
}
