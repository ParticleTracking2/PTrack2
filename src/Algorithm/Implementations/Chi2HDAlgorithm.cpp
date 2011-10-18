/*
 * Chi2Algorithm.cpp
 *
 *  Created on: 12-06-2011
 *      Author: juanin
 */

#include "Chi2HDAlgorithm.h"

vector<MyPeak> Chi2HDAlgorithm::run(ParameterContainer *pc){
	MyLogger::log()->notice("[Chi2HDAlgorithm] Running Chi2 High Density Algorithm");
	double d = pc->getParamAsDouble("-d");
	double w = pc->getParamAsDouble("-w");

	unsigned int ss = 2*floor(d/2 + 4*w/2)-1;
	unsigned int os = (ss-1)/2;

	MyLogger::log()->info("[Chi2HDAlgorithm] ***************************** ");
	MyLogger::log()->info("[Chi2HDAlgorithm] 1. Normalize image ");
	Chi2Lib::normalizeImage(data);

	MyLogger::log()->info("[Chi2HDAlgorithm] ***************************** ");
	MyLogger::log()->info("[Chi2HDAlgorithm] 2. Generate Chi2 image ");
	MyMatrix<double> kernel = Chi2Lib::generateKernel(ss,os,d,w);
	MyMatrix<double> chi_img(data->sX()+kernel.sX()-1, data->sY()+kernel.sY()-1);
	Chi2LibFFTW::getChiImage(&kernel, data, &chi_img);	// ~430|560 -> |290 Milisegundos

	MyLogger::log()->info("[Chi2HDAlgorithm] ***************************** ");
	MyLogger::log()->info("[Chi2HDAlgorithm] 3. Obtain peaks of Chi2 Image ");
	unsigned int threshold = 5, minsep = 1, mindistance = 5;
	vector<MyPeak> peaks = Chi2Lib::getPeaks(&chi_img, threshold, mindistance, minsep); // ~120|150 -> |125 Milisegundos

	MyLogger::log()->info("[Chi2HDAlgorithm] ***************************** ");
	MyLogger::log()->info("[Chi2HDAlgorithm] 4. Generate Auxiliary Matrix ");
	MyMatrix<double> grid_x(data->sX(), data->sY());
	MyMatrix<double> grid_y(data->sX(), data->sY());
	MyMatrix<int> over(data->sX(), data->sY());
	Chi2Lib::generateGrid(&peaks, os, data, &grid_x, &grid_y, &over);	// ~170|200 -> |150 Milisegundos

	MyLogger::log()->info("[Chi2HDAlgorithm] ***************************** ");
	FileUtils::writeToFileM(&grid_x, "gridx.txt");
	FileUtils::writeToFileM(&grid_y, "gridy.txt");
	FileUtils::writeToFileM(&over, "over.txt");

	MyLogger::log()->info("[Chi2HDAlgorithm] 5. Compute Chi2 Difference ");
	MyMatrix<double> chi2diff(data->sX(), data->sY());
	double currentChi2Error = Chi2Lib::computeDifference(data, &grid_x, &grid_y, d, w, &chi2diff); // ~70|80 -> |50 Milisegundos

	MyLogger::log()->info("[Chi2HDAlgorithm] ***************************** ");
	MyLogger::log()->info("[Chi2HDAlgorithm] 6. Add missed points ");
	unsigned int chi_cut = 2;
	unsigned int total_found = 0;
	MyMatrix<double> normaldata_chi(data->sX(), data->sY()); // No necesita reset

	unsigned int _maxIterations = 5, iterations = 0;
	while(iterations <= _maxIterations){
		MyLogger::log()->info("[Chi2HDAlgorithm] 6.1. Generating Scaled Image ");
		Chi2LibHighDensity::generateScaledImage(&chi2diff, &normaldata_chi); // ~ 15 Milisegundos

		MyLogger::log()->info("[Chi2HDAlgorithm] 6.2. Obtaining new CHi2 Image ");
		Chi2LibFFTW::getChiImage(&kernel, &normaldata_chi, &chi_img); // ~390|500 -> |220 Milisegundos

		MyLogger::log()->info("[Chi2HDAlgorithm] 6.3. Obtaining new Peaks ");
		vector<MyPeak> new_peaks = Chi2Lib::getPeaks(&chi_img, chi_cut, mindistance, minsep); // ~7 Milisegundos

		unsigned int old_size = peaks.size();
		MyLogger::log()->info("[Chi2HDAlgorithm] 6.4. Checking inside image peaks ");
		unsigned int found = Chi2LibHighDensity::checkInsidePeaks(&peaks, &new_peaks, data, os); // 0 Milisegundos
		total_found += found;

		if(found <= 0)
			break;

		MyLogger::log()->info("[Chi2HDAlgorithm] 6.5. Generating Auxiliary Matrix ");
		Chi2Lib::generateGrid(&peaks,os, data, &grid_x, &grid_y, &over); // ~200 Milisegundos

		MyLogger::log()->info("[Chi2HDAlgorithm] 6.6. Computing Chi2 Difference ");
		currentChi2Error = Chi2Lib::computeDifference(data, &grid_x, &grid_y, d, w, &chi2diff); // ~80 Milisegundos

		MyLogger::log()->info("[Chi2HDAlgorithm] Original No of Points: %i, +%i; Total Found = %i", old_size, found, total_found);

		iterations++;
	}
	sort(peaks.begin(), peaks.end(), MyPeak::compareMe);
	Chi2LibFFTWCache::eraseAll();

	MyLogger::log()->info("[Chi2HDAlgorithm] ***************************** ");
	MyLogger::log()->info("[Chi2HDAlgorithm] 7. Recompute Auxiliary matrix and Chi2 Difference");
	MyLogger::log()->info("[Chi2HDAlgorithm] 7.1. Recompute Auxiliary matrix");
	Chi2Lib::generateGrid(&peaks,os, data, &grid_x, &grid_y, &over);
	MyLogger::log()->info("[Chi2HDAlgorithm] 7.2. Recompute Chi2 Difference");
	currentChi2Error = Chi2Lib::computeDifference(data, &grid_x, &grid_y, d, w, &chi2diff);

	MyLogger::log()->info("[Chi2HDAlgorithm] ***************************** ");
	MyLogger::log()->info("[Chi2HDAlgorithm] 8. Minimizing Chi2 Error ");
	unsigned int _minChi2Delta = 1;
	iterations = 0; _maxIterations = 5;
	double chi2Delta = currentChi2Error;

	while( fabs(chi2Delta) > _minChi2Delta &&  iterations < _maxIterations){
		Chi2Lib::newtonCenter(&over, &chi2diff, &peaks, os, d, w, ss); // ~400 -> ~250 Milisegundos

		for(unsigned int i=0; i < peaks.size(); ++i){
			peaks.at(i).px = peaks.at(i).px + peaks.at(i).dpx;
			peaks.at(i).py = peaks.at(i).py + peaks.at(i).dpy;

			peaks.at(i).x = (unsigned int)round(peaks.at(i).px);
			peaks.at(i).y = (unsigned int)round(peaks.at(i).py);
		}

		Chi2Lib::generateGrid(&peaks, os, data, &grid_x, &grid_y, &over);
		Chi2LibMatrix::fillWith(&chi2diff, 0);

		double newChi2Err = Chi2Lib::computeDifference(data, &grid_x, &grid_y, d, w, &chi2diff);
		chi2Delta = currentChi2Error - newChi2Err;
		currentChi2Error = currentChi2Error-chi2Delta;
		iterations++;
	}


	MyLogger::log()->info("[Chi2HDAlgorithm] ***************************** ");
	MyLogger::log()->info("[Chi2HDAlgorithm] 9. Checking particles by pixel intensity and voronoi area Tom's algorithm ");

	//for each valid point (inside) build the histogram
	//compute mu & sigma for the histogram
	MyLogger::log()->info("[Chi2HDAlgorithm] 9.1. Remove outside image peaks");
	Chi2LibHighDensity::filterPeaksOutside(&peaks, data, os);

	MyLogger::log()->info("[Chi2HDAlgorithm] 9.2. Apply Gaussian Fit ");
	pair<double,double> mypair = Chi2LibHighDensity::gaussianFit(&peaks, data, os);
	double mu = mypair.first;
	double sigma = mypair.second;


	MyLogger::log()->info("[Chi2HDAlgorithm] 9.3. Filter 'Bad' Peaks using Voronoy Area and intensity");
	double par_thresh=mu-3.0*sigma;
	double vor_thresh = 50.0;
	Chi2LibHighDensity::removeBadPeaks(&peaks, data, vor_thresh, par_thresh, os);

	MyLogger::log()->info("[Chi2HDAlgorithm] ***************************** ");
	MyLogger::log()->info("[Chi2HDAlgorithm] 9.4. Recompute Auxiliary matrix and Chi2 Difference");
	MyLogger::log()->info("[Chi2HDAlgorithm] 9.4.1. Recompute Auxiliary matrix");
	Chi2Lib::generateGrid(&peaks,os, data, &grid_x, &grid_y, &over);
	MyLogger::log()->info("[Chi2HDAlgorithm] 9.4.2. Recompute Chi2 Difference");
	Chi2Lib::computeDifference(data, &grid_x, &grid_y, d, w, &chi2diff);
	chi2Delta = 1000000.0;
	iterations = 0;
	MyLogger::log()->info("[Chi2HDAlgorithm] ***************************** ");
	MyLogger::log()->info("[Chi2HDAlgorithm] 9.5. Minimizing Chi2 Error ");
	while( fabs(chi2Delta) > _minChi2Delta &&  iterations < _maxIterations){
		Chi2Lib::newtonCenter(&over, &chi2diff, &peaks, os, d, w, ss);

		for(unsigned int i=0; i < peaks.size(); ++i){
			peaks.at(i).px = peaks.at(i).px + peaks.at(i).dpx;
			peaks.at(i).py = peaks.at(i).py + peaks.at(i).dpy;

			peaks.at(i).x = (unsigned int)round(peaks.at(i).px);
			peaks.at(i).y = (unsigned int)round(peaks.at(i).py);
		}

		Chi2Lib::generateGrid(&peaks, os, data, &grid_x, &grid_y, &over);
		Chi2LibMatrix::fillWith(&chi2diff, 0);

		double newChi2Err = Chi2Lib::computeDifference(data, &grid_x, &grid_y, d, w, &chi2diff);
		chi2Delta = currentChi2Error - newChi2Err;
		currentChi2Error = currentChi2Error-chi2Delta;
		iterations++;
	}
	MyLogger::log()->info("[Chi2HDAlgorithm] ***************************** ");
	MyLogger::log()->info("[Chi2HDAlgorithm] 9.6. Recomputing Voronoi areas ");
	Chi2LibQhull::addVoronoiAreas(&peaks);
	Chi2Lib::transformPeaks(&peaks, os, data->sX());
	return peaks;
}
