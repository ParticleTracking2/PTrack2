/*
 * Chi2Algorithm.cpp
 *
 *  Created on: 12-06-2011
 *      Author: juanin
 */

#include "Chi2HDAlgorithm.h"

ArgObj Chi2HDAlgorithm::myArgs(){
	ArgObj chi2hd;
	chi2hd.type = Chi2HD_Algorithm;
	chi2hd.argkey = "chi2hd";
	chi2hd.description = "Convolution based least-squares fitting for High density particle systems.";
	chi2hd.example = "chi2hd -i MyImage.tif -d 9.87 -w 1.84";

	/* Parametros aceptables */
	KeyTreat img; img.key = "-i"; img.description = "Image to read.";
	img.treat.push_back(Require_Treat);
	img.treat.push_back(Followed_String_Treat);
	chi2hd.keys_treats.push_back(img);

	KeyTreat d; d.key = "-d"; d.description = "Diameter of an ideal particle. (Default = 9.87).";
	d.treat.push_back(Followed_Double_Treat);
	chi2hd.keys_treats.push_back(d);

	KeyTreat w; w.key = "-w"; w.description = "Value of how sharply the ideal particle is viewed (Focus). (Default = 1.84).";
	w.treat.push_back(Followed_Double_Treat);
	chi2hd.keys_treats.push_back(w);

	KeyTreat cut; cut.key = "-cut"; cut.description = "Crop image by each side (in pixels).";
	cut.treat.push_back(Followed_Int_Treat);
	chi2hd.keys_treats.push_back(cut);

	KeyTreat maxchi2miniter; maxchi2miniter.key = "-maxchi2miniter"; maxchi2miniter.description = "Limit the iteration for minimizing Chi2Error (Default = 5).";
	maxchi2miniter.treat.push_back(Followed_Int_Treat);
	chi2hd.keys_treats.push_back(maxchi2miniter);

	KeyTreat minsep; minsep.key = "-minsep"; minsep.description = "Minimal Separations between peaks. (Default 1)";
	minsep.treat.push_back(Followed_Int_Treat);
	chi2hd.keys_treats.push_back(minsep);
	
	KeyTreat chi_cut; chi_cut.key = "-chicut"; chi_cut.description = "Minimal intensity of the convolution peaks to be detected.";
	chi_cut.treat.push_back(Followed_Double_Treat);
	chi2hd.keys_treats.push_back(chi_cut);

	KeyTreat vor_cut; vor_cut.key = "-vorcut"; vor_cut.description = "Minimal Voronoi area acceptable of peak to be considered as peak.";
	vor_cut.treat.push_back(Followed_Double_Treat);
	chi2hd.keys_treats.push_back(vor_cut);

	KeyTreat vor_sl; vor_sl.key = "-vorsl"; vor_sl.description = "Voronoi area value division of solid and liquid particle.";
	vor_sl.treat.push_back(Followed_Double_Treat);
	chi2hd.keys_treats.push_back(vor_sl);

	KeyTreat filter2i; filter2i.key = "-2filteri"; filter2i.description = "Second Filter of Bad particles using Image intensity Only.";
	filter2i.treat.push_back(Followed_Double_Treat);
	chi2hd.keys_treats.push_back(filter2i);

	KeyTreat filter2v; filter2v.key = "-2filterv"; filter2v.description = "Second Filter of Bad particles using Voronoi area Only.";
	filter2v.treat.push_back(Followed_Double_Treat);
	chi2hd.keys_treats.push_back(filter2v);

	return chi2hd;
}

void Chi2HDAlgorithm::setData(ParameterContainer *pc){
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

	_chi_cut = 2;
	if(pc->existParam("-chicut"))
		_chi_cut = pc->getParamAsDouble("-chicut");

	_vor_thresh = 50.0;
	if(pc->existParam("-vorcut"))
		_vor_thresh = pc->getParamAsDouble("-vorcut");

	_vor_areaSL = 75.0;
	if(pc->existParam("-vorsl"))
		_vor_areaSL = pc->getParamAsDouble("-vorsl");

	_FilterI = 1.0;
	_secondFilterI = false;
	if(pc->existParam("-2filteri")){
		_secondFilterI = true;
		_FilterI = pc->getParamAsDouble("-2filteri");
	}

	_FilterV = 1.0;
	_secondFilterV = false;
	if(pc->existParam("-2filterv")){
		_secondFilterV = true;
		_FilterV = pc->getParamAsDouble("-2filterv");
	}

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
vector<MyPeak> Chi2HDAlgorithm::run(){
	MyLogger::log()->notice("[Chi2HDAlgorithm] Running Chi2 High Density Algorithm");

	int ss = 2*floor(_d/2 + 4*_w/2)-1;
	int os = (ss-1)/2;

	MyLogger::log()->info("[Chi2HDAlgorithm] ***************************** ");
	MyLogger::log()->info("[Chi2HDAlgorithm] >> Normalize image ");
	Chi2Lib::normalizeImage(&_data);

	MyLogger::log()->info("[Chi2HDAlgorithm] ***************************** ");
	MyLogger::log()->info("[Chi2HDAlgorithm] >> Generate Chi2 image ");
	MyMatrix<double> kernel = Chi2Lib::generateKernel(ss, os, _d, _w);
	MyMatrix<double> chi_img(_data.sX()+kernel.sX()-1, _data.sY()+kernel.sY()-1);
	Chi2LibFFTW::getChiImage(&kernel, &_data, &chi_img, use_threads);	// ~430|560 -> |290 Milisegundos

	MyLogger::log()->info("[Chi2HDAlgorithm] ***************************** ");
	MyLogger::log()->info("[Chi2HDAlgorithm] >> Obtain peaks of Chi2 Image ");
	unsigned int threshold = 5, minsep = _minsep, mindistance = 5;
	vector<MyPeak> peaks = Chi2Lib::getPeaks(&chi_img, threshold, mindistance, minsep, use_threads); // ~120|150 -> |125 Milisegundos

	MyLogger::log()->info("[Chi2HDAlgorithm] ***************************** ");
	MyLogger::log()->info("[Chi2HDAlgorithm] >> Generate Auxiliary Matrix ");
	MyLogger::log()->debug("[Chi2HDAlgorithm] >> Allocating %ix%i", _data.sX(), _data.sY());
	MyMatrix<double> grid_x(_data.sX(), _data.sY());
	MyMatrix<double> grid_y(_data.sX(), _data.sY());
	MyMatrix<int> over(_data.sX(), _data.sY());
	MyLogger::log()->debug("[Chi2HDAlgorithm] >> Allocation Complete ");
	Chi2Lib::generateGrid(&peaks, os, &_data, &grid_x, &grid_y, &over, use_threads);	// ~170|200 -> |150 Milisegundos

	MyLogger::log()->info("[Chi2HDAlgorithm] ***************************** ");
	MyLogger::log()->info("[Chi2HDAlgorithm] >> Compute Chi2 Difference ");
	MyMatrix<double> chi2diff(_data.sX(), _data.sY());
	double currentChi2Error = Chi2Lib::computeDifference(&_data, &grid_x, &grid_y, _d, _w, &chi2diff, use_threads); // ~70|80 -> |50 Milisegundos

	MyLogger::log()->info("[Chi2HDAlgorithm] ***************************** ");
	MyLogger::log()->info("[Chi2HDAlgorithm] >> Add missed points ");

	unsigned int total_found = 0;
	MyMatrix<double> normaldata_chi(_data.sX(), _data.sY()); // No necesita reset

	unsigned int _maxFirstIterations = 10, iterations = 0;
	while(iterations <= _maxFirstIterations){
		MyLogger::log()->info("[Chi2HDAlgorithm] >> Generating Scaled Image ");
		Chi2LibHighDensity::generateScaledImage(&chi2diff, &normaldata_chi); // ~ 15 Milisegundos

		MyLogger::log()->info("[Chi2HDAlgorithm] >> Obtaining new CHi2 Image ");
		Chi2LibFFTW::getChiImage(&kernel, &normaldata_chi, &chi_img, use_threads); // ~390|500 -> |220 Milisegundos

		MyLogger::log()->info("[Chi2HDAlgorithm] >> Obtaining new Peaks ");
		vector<MyPeak> new_peaks = Chi2Lib::getPeaks(&chi_img, _chi_cut, mindistance, minsep, use_threads); // ~7 Milisegundos

		unsigned int old_size = peaks.size();
		MyLogger::log()->info("[Chi2HDAlgorithm] >> Checking inside image peaks ");
		unsigned int found = Chi2LibHighDensity::checkInsidePeaks(&peaks, &new_peaks, &_data, os); // 0 Milisegundos
		total_found += found;

		if(found <= 0)
			break;

		MyLogger::log()->info("[Chi2HDAlgorithm] >> Generating Auxiliary Matrix ");
		Chi2Lib::generateGrid(&peaks, os, &_data, &grid_x, &grid_y, &over, use_threads); // ~200 Milisegundos

		MyLogger::log()->info("[Chi2HDAlgorithm] >> Computing Chi2 Difference ");
		currentChi2Error = Chi2Lib::computeDifference(&_data, &grid_x, &grid_y, _d, _w, &chi2diff, use_threads); // ~80 Milisegundos

		MyLogger::log()->info("[Chi2HDAlgorithm] >> Original No of Points: %i, +%i; Total Found = %i", old_size, found, total_found);

		iterations++;
	}
	sort(peaks.begin(), peaks.end(), MyPeak::compareMe);
	Chi2LibFFTWCache::eraseAll();

	MyLogger::log()->info("[Chi2HDAlgorithm] ***************************** ");
	MyLogger::log()->info("[Chi2HDAlgorithm] >> Recompute Auxiliary matrix and Chi2 Difference");
	MyLogger::log()->info("[Chi2HDAlgorithm] >> Recompute Auxiliary matrix");
	Chi2Lib::generateGrid(&peaks, os, &_data, &grid_x, &grid_y, &over, use_threads);

	MyLogger::log()->info("[Chi2HDAlgorithm] >> Recompute Chi2 Difference");
	currentChi2Error = Chi2Lib::computeDifference(&_data, &grid_x, &grid_y, _d, _w, &chi2diff, use_threads);

	MyLogger::log()->info("[Chi2HDAlgorithm] ***************************** ");
	MyLogger::log()->info("[Chi2HDAlgorithm] >> Minimizing Chi2 Error ");
	unsigned int _minChi2Delta = 1;
	iterations = 0;
	double chi2Delta = currentChi2Error;

	while( fabs(chi2Delta) > _minChi2Delta &&  iterations < _maxIterations){
		Chi2Lib::newtonCenter(&over, &chi2diff, &peaks, os, _d, _w, ss, 20.0, use_threads); // ~400 -> ~250 Milisegundos

		for(unsigned int i=0; i < peaks.size(); ++i){
			peaks.at(i).px = peaks.at(i).px + peaks.at(i).dpx;
			peaks.at(i).py = peaks.at(i).py + peaks.at(i).dpy;

			peaks.at(i).x = (unsigned int)rint(peaks.at(i).px);
			peaks.at(i).y = (unsigned int)rint(peaks.at(i).py);
		}

		Chi2Lib::generateGrid(&peaks, os, &_data, &grid_x, &grid_y, &over, use_threads);
		chi2diff.reset(0);

		double newChi2Err = Chi2Lib::computeDifference(&_data, &grid_x, &grid_y, _d, _w, &chi2diff, use_threads);
		MyLogger::log()->info("[Chi2HDAlgorithm] >> Chi2Error: %f", newChi2Err);
		chi2Delta = currentChi2Error - newChi2Err;
		currentChi2Error = currentChi2Error-chi2Delta;
		iterations++;
	}

	MyLogger::log()->info("[Chi2HDAlgorithm] ***************************** ");
	MyLogger::log()->info("[Chi2HDAlgorithm] >> Checking particles by pixel intensity and voronoi area Tom's algorithm ");

	//for each valid point (inside) build the histogram
	//compute mu & sigma for the histogram
	MyLogger::log()->info("[Chi2HDAlgorithm] >> Remove outside image peaks");
	Chi2LibHighDensity::filterPeaksOutside(&peaks, &_data, os);

	MyLogger::log()->info("[Chi2HDAlgorithm] >> Apply Gaussian Fit ");
	pair<double,double> mypair = Chi2LibHighDensity::gaussianFit(&peaks, &_data, os);
	double mu = mypair.first;
	double sigma = mypair.second;
	MyLogger::log()->info("[Chi2HDAlgorithm] >> Total peaks: %i; MU=%f; SIGMA=%f", peaks.size(), mu, sigma);

	MyLogger::log()->info("[Chi2HDAlgorithm] ***************************** ");
	double par_thresh = mu-3.0*sigma;

	MyLogger::log()->info("[Chi2HDAlgorithm] >> Filter 'Bad' Peaks using Voronoi Area: %f - Intensity: %f", _vor_thresh, par_thresh);
	Chi2LibHighDensity::removeBadPeaks(&peaks, &_data, _vor_thresh, par_thresh, os);

	if(_secondFilterI){
		MyLogger::log()->info("[Chi2HDAlgorithm] >> Second Filter 'Bad' Peaks using intensity");
		unsigned int old_total  = peaks.size();
		Chi2LibHighDensity::removeBadIntensityPeaks(&peaks, &_data, _FilterI, os);
		unsigned int new_total  = peaks.size();
		MyLogger::log()->info("[Chi2HDAlgorithm] >> New Number of peaks: %i, Filtered :%i", new_total, (old_total - new_total));
	}

	if(_secondFilterV){
		MyLogger::log()->info("[Chi2HDAlgorithm] >> Second Filter 'Bad' Peaks using Voronoi Area");
		unsigned int old_total  = peaks.size();
		Chi2LibHighDensity::removeBadVoronoiPeaks(&peaks, &_data, _FilterV, os);
		unsigned int new_total  = peaks.size();
		MyLogger::log()->info("[Chi2HDAlgorithm] >> New Number of peaks: %i, Filtered :%i", new_total, (old_total - new_total));
	}

	MyLogger::log()->info("[Chi2HDAlgorithm] ***************************** ");
	MyLogger::log()->info("[Chi2HDAlgorithm] >> Recompute Auxiliary matrix and Chi2 Difference");
	MyLogger::log()->info("[Chi2HDAlgorithm] >> Recompute Auxiliary matrix");
	Chi2Lib::generateGrid(&peaks,os, &_data, &grid_x, &grid_y, &over, use_threads);
	MyLogger::log()->info("[Chi2HDAlgorithm] >> Recompute Chi2 Difference");
	Chi2Lib::computeDifference(&_data, &grid_x, &grid_y, _d, _w, &chi2diff, use_threads);
	chi2Delta = 1000000.0;
	iterations = 0;
	MyLogger::log()->info("[Chi2HDAlgorithm] ***************************** ");
	MyLogger::log()->info("[Chi2HDAlgorithm] >> Minimizing Chi2 Error ");

	while( fabs(chi2Delta) > _minChi2Delta &&  iterations < _maxIterations){
		Chi2Lib::newtonCenter(&over, &chi2diff, &peaks, os, _d, _w, ss, 20.0, use_threads);

		for(unsigned int i=0; i < peaks.size(); ++i){
			peaks.at(i).px = peaks.at(i).px + peaks.at(i).dpx;
			peaks.at(i).py = peaks.at(i).py + peaks.at(i).dpy;

			peaks.at(i).x = (unsigned int)rint(peaks.at(i).px);
			peaks.at(i).y = (unsigned int)rint(peaks.at(i).py);
		}

		Chi2Lib::generateGrid(&peaks, os, &_data, &grid_x, &grid_y, &over, use_threads);
		chi2diff.reset(0);

		double newChi2Err = Chi2Lib::computeDifference(&_data, &grid_x, &grid_y, _d, _w, &chi2diff, use_threads);
		MyLogger::log()->info("[Chi2HDAlgorithm] >> Chi2Error: %f", newChi2Err);
		chi2Delta = currentChi2Error - newChi2Err;
		currentChi2Error = currentChi2Error-chi2Delta;
		iterations++;
	}

	MyLogger::log()->info("[Chi2HDAlgorithm] ***************************** ");
	MyLogger::log()->info("[Chi2HDAlgorithm] >> Recomputing Voronoi areas ");
	Chi2LibQhull::addVoronoiAreas(&peaks);

	MyLogger::log()->info("[Chi2HDAlgorithm] >> Translating coordenates ");
	Chi2Lib::translatePeaks(&peaks, os);

	MyLogger::log()->info("[Chi2HDAlgorithm] >> Adding State ");
	Chi2Lib::addState(&peaks, _vor_areaSL);

	return peaks;
}
