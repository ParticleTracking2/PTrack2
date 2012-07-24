/*
 * Chi2Algorithm.cpp
 *
 *  Created on: 12-06-2011
 *      Author: juanin
 */

#include "Chi2Algorithm.h"

ArgObj Chi2Algorithm::myArgs(){
	ArgObj chi2;
	chi2.type = Chi2_Algorithm;
	chi2.argkey = "chi2";
	chi2.description = "Convolution based least-squares fitting.";
	chi2.example = "chi2 -i MyImage.tif -d 9.87 -w 1.84";

	/* Parametros aceptables */
	KeyTreat img; img.key = "-i"; img.description = "Image to read.";
	img.treat.push_back(Require_Treat);
	img.treat.push_back(Followed_String_Treat);
	chi2.keys_treats.push_back(img);

	KeyTreat d; d.key = "-d"; d.description = "Diameter of an ideal particle. (Default = 9.87).";
	d.treat.push_back(Followed_Double_Treat);
	chi2.keys_treats.push_back(d);

	KeyTreat w; w.key = "-w"; w.description = "Value of how sharply the ideal particle is viewed (Focus). (Default = 1.84).";
	w.treat.push_back(Followed_Double_Treat);
	chi2.keys_treats.push_back(w);

	KeyTreat cut; cut.key = "-cut"; cut.description = "Crop image by each side (in pixels).";
	cut.treat.push_back(Followed_Int_Treat);
	chi2.keys_treats.push_back(cut);
	
	KeyTreat minsep; minsep.key = "-minsep"; minsep.description = "Minimal Separations between peaks. (Default 1)";
	minsep.treat.push_back(Followed_Int_Treat);
	chi2.keys_treats.push_back(minsep);

	KeyTreat maxchi2miniter; maxchi2miniter.key = "-maxchi2miniter"; maxchi2miniter.description = "Limit the iteration for minimizing Chi2Error (Default = 5).";
	maxchi2miniter.treat.push_back(Followed_Int_Treat);
	chi2.keys_treats.push_back(maxchi2miniter);

	return chi2;
}

void Chi2Algorithm::setData(ParameterContainer *pc){
	_d = 9.87;
	if(pc->existParam("-d"))
		_d = pc->getParamAsDouble("-d");

	_w = 1.84;
	if(pc->existParam("-w"))
		_w = pc->getParamAsDouble("-w");

	_minsep = 1;
	if(pc->existParam("-minsep"))
		_minsep = pc->getParamAsInt("-minsep");
		
	_maxIterations = 5;
	if(pc->existParam("-maxchi2miniter"))
		_maxIterations = pc->getParamAsInt("-maxchi2miniter");

	if(pc->existParam("-cut"))
		_data = MyImageFactory::makeRawImgFromFile(pc->getParamAsString("-i"), pc->getParamAsInt("-cut"));
	else
		_data = MyImageFactory::makeRawImgFromFile(pc->getParamAsString("-i"));
}

/**
 *******************************
 * Ejecutar Algoritmo
 *******************************
 */
vector<MyPeak> Chi2Algorithm::run(){
	MyLogger::log()->notice("[Chi2Algorithm] Running Chi2 Algorithm");

	unsigned int ss = 2*floor(_d/2 + 4*_w/2)-1;
	unsigned int os = (ss-1)/2;

	MyLogger::log()->info("[Chi2Algorithm] ***************************** ");
	MyLogger::log()->info("[Chi2Algorithm] >> Normalize image ");
	Chi2Lib::normalizeImage(&_data);

	MyLogger::log()->info("[Chi2Algorithm] ***************************** ");
	MyLogger::log()->info("[Chi2Algorithm] >> Generate Chi2 image ");
	MyMatrix<double> kernel = Chi2Lib::generateKernel(ss, os, _d, _w);
	MyMatrix<double> chi_img(_data.sX()+kernel.sX()-1, _data.sY()+kernel.sY()-1);
	Chi2LibFFTW::getChiImage(&kernel, &_data, &chi_img);

	MyLogger::log()->info("[Chi2Algorithm] ***************************** ");
	MyLogger::log()->info("[Chi2Algorithm] >> Obtain peaks of Chi2 Image ");
	unsigned int threshold = 5, minsep = _minsep, mindistance = 5;
	vector<MyPeak> peaks = Chi2Lib::getPeaks(&chi_img, threshold, mindistance, minsep, use_threads);

	MyLogger::log()->info("[Chi2Algorithm] ***************************** ");
	MyLogger::log()->info("[Chi2Algorithm] >> Generate Auxiliary Matrix ");
	MyMatrix<double> grid_x(_data.sX(), _data.sY());
	MyMatrix<double> grid_y(_data.sX(), _data.sY());
	MyMatrix<int> over(_data.sX(), _data.sY());
	Chi2Lib::generateGrid(&peaks, os, &_data, &grid_x, &grid_y, &over);

	MyLogger::log()->info("[Chi2Algorithm] ***************************** ");
	MyLogger::log()->info("[Chi2Algorithm] >> Compute Chi2 Difference ");
	MyMatrix<double> chi2diff(_data.sX(), _data.sY());
	double currentChi2Error = Chi2Lib::computeDifference(&_data, &grid_x, &grid_y, _d, _w, &chi2diff, use_threads);

	MyLogger::log()->info("[Chi2Algorithm] ***************************** ");
	MyLogger::log()->info("[Chi2Algorithm] >> Minimizing Chi2 Error ");
	unsigned int _minChi2Delta = 1;
	unsigned int iterations = 0;
	double chi2Delta = currentChi2Error;

	while( fabs(chi2Delta) > _minChi2Delta &&  iterations < _maxIterations){
		Chi2Lib::newtonCenter(&over, &chi2diff, &peaks, os, _d, _w, ss);

		for(unsigned int i=0; i < peaks.size(); ++i){
			peaks.at(i).px = peaks.at(i).px + peaks.at(i).dpx;
			peaks.at(i).py = peaks.at(i).py + peaks.at(i).dpy;

			peaks.at(i).x = (unsigned int)round(peaks.at(i).px);
			peaks.at(i).y = (unsigned int)round(peaks.at(i).py);
		}

		Chi2Lib::generateGrid(&peaks, os, &_data, &grid_x, &grid_y, &over, use_threads);
		chi2diff.reset(0);

		double newChi2Err = Chi2Lib::computeDifference(&_data, &grid_x, &grid_y, _d, _w, &chi2diff, use_threads);
		chi2Delta = currentChi2Error - newChi2Err;
		currentChi2Error = currentChi2Error-chi2Delta;
		iterations++;
	}
	MyLogger::log()->info("[Chi2HDAlgorithm] ***************************** ");
	MyLogger::log()->info("[Chi2HDAlgorithm] >> Computing Voronoi areas ");
	Chi2LibQhull::addVoronoiAreas(&peaks);
	Chi2Lib::addState(&peaks);
	Chi2Lib::translatePeaks(&peaks, os);

	return peaks;
}
