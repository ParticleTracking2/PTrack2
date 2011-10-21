/*
 * Chi2Algorithm.cpp
 *
 *  Created on: 12-06-2011
 *      Author: juanin
 */

#include "Chi2Algorithm.h"

vector<MyPeak> Chi2Algorithm::run(ParameterContainer *pc){
	MyLogger::log()->notice("[Chi2Algorithm] Running Chi2 Algorithm");
	double d = pc->getParamAsDouble("-d");
	double w = pc->getParamAsDouble("-w");

	unsigned int ss = 2*floor(d/2 + 4*w/2)-1;
	unsigned int os = (ss-1)/2;

	MyLogger::log()->info("[Chi2Algorithm] ***************************** ");
	MyLogger::log()->info("[Chi2Algorithm] 1. Normalize image ");
	Chi2Lib::normalizeImage(data);

	MyLogger::log()->info("[Chi2Algorithm] ***************************** ");
	MyLogger::log()->info("[Chi2Algorithm] 2. Generate Chi2 image ");
	MyMatrix<double> kernel = Chi2Lib::generateKernel(ss,os,d,w);
	MyMatrix<double> chi_img(data->sX()+kernel.sX()-1, data->sY()+kernel.sY()-1);
	Chi2LibFFTW::getChiImage(&kernel, data, &chi_img);

	MyLogger::log()->info("[Chi2Algorithm] ***************************** ");
	MyLogger::log()->info("[Chi2Algorithm] 3. Obtain peaks of Chi2 Image ");
	unsigned int threshold = 5, minsep = 1, mindistance = 5;
	vector<MyPeak> peaks = Chi2Lib::getPeaks(&chi_img, threshold, mindistance, minsep);

	MyLogger::log()->info("[Chi2Algorithm] ***************************** ");
	MyLogger::log()->info("[Chi2Algorithm] 4. Generate Auxiliary Matrix ");
	MyMatrix<double> grid_x(data->sX(), data->sY());
	MyMatrix<double> grid_y(data->sX(), data->sY());
	MyMatrix<int> over(data->sX(), data->sY());
	Chi2Lib::generateGrid(&peaks, os, data, &grid_x, &grid_y, &over);

	MyLogger::log()->info("[Chi2Algorithm] ***************************** ");
	MyLogger::log()->info("[Chi2Algorithm] 5. Compute Chi2 Difference ");
	MyMatrix<double> chi2diff(data->sX(), data->sY());
	double currentChi2Error = Chi2Lib::computeDifference(data, &grid_x, &grid_y, d, w, &chi2diff);

	MyLogger::log()->info("[Chi2Algorithm] ***************************** ");
	MyLogger::log()->info("[Chi2Algorithm] 6. Minimizing Chi2 Error ");
	unsigned int _maxIterations = 5, _minChi2Delta = 1;
	unsigned int iterations = 0;
	double chi2Delta = currentChi2Error;

	while( fabs(chi2Delta) > _minChi2Delta &&  iterations < _maxIterations){
		MyLogger::log()->info("[Chi2Algorithm] 6. >> Starting iteration No=%i",iterations);
		Chi2Lib::newtonCenter(&over, &chi2diff, &peaks, os, d, w, ss);

		for(unsigned int i=0; i < peaks.size(); ++i){
			peaks.at(i).px = peaks.at(i).px + peaks.at(i).dpx;
			peaks.at(i).py = peaks.at(i).py + peaks.at(i).dpy;

			peaks.at(i).x = (unsigned int)round(peaks.at(i).px);
			peaks.at(i).y = (unsigned int)round(peaks.at(i).py);
		}

		Chi2Lib::generateGrid(&peaks, os, data, &grid_x, &grid_y, &over);
		chi2diff.reset(0);

		double newChi2Err = Chi2Lib::computeDifference(data, &grid_x, &grid_y, d, w, &chi2diff);
		chi2Delta = currentChi2Error - newChi2Err;
		currentChi2Error = currentChi2Error-chi2Delta;
		iterations++;
		MyLogger::log()->info("[Chi2Algorithm] 6. >> Iteration ended ");
	}
	MyLogger::log()->info("[Chi2HDAlgorithm] ***************************** ");
	MyLogger::log()->info("[Chi2HDAlgorithm] 7. Computing Voronoi areas ");
	Chi2LibQhull::addVoronoiAreas(&peaks);
	Chi2Lib::transformPeaks(&peaks, os, data->sX());

	return peaks;
}
