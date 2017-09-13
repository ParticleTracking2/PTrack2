/*
 * Chi2Algorithm.cpp
 *
 *  Created on: 12-06-2011
 *      Author: juanin
 */

#include "Chi2Algorithm.h"
#include <cstdio>
#include <cstdlib>
#include <omp.h>

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

    printf("scanning string: %s\n", pc->getParamAsString("-i").c_str());
    sscanf(pc->getParamAsString("-i").c_str(), "%[^_]_fD%f_A%i_B%i_L%i_N%i_NC%i_d%f.tif", prefix, &fD, &A, &B, &L, &Nreal, &Nc, &density);
    printf("parsed:\nprefix:%s\nfD:%f\nA:%i\nB:%i\nL:%i\nN:%i\nNC:%i\nd:%f\n", prefix, fD, A, B, L, Nreal, Nc, density);
}

/**
 *******************************
 * Ejecutar Algoritmo
 *******************************
 */

void msgenter(const char *format, float aux){
    printf(format, aux);
    getchar();
}

vector<MyPeak> Chi2Algorithm::run(){
    double t1, t2, rt1, rt2;
    FILE *fw_times = fopen("chi2_times.dat", "a");
    float time_chi2 = 0.0f, time_getpeaks = 0.0f, time_newtoncenter = 0.0f, time_normalize = 0.0f, time_fft = 0.0f, time_qhull = 0.0f, time_gengrid = 0.0f, time_functions = 0.0f, time_rest = 0.0f, time_run = 0.0f;
    rt1 = omp_get_wtime();




	MyLogger::log()->notice("[Chi2Algorithm] Running Chi2 Algorithm");

	unsigned int ss = 2*floor(_d/2 + 4*_w/2)-1;
	unsigned int os = (ss-1)/2;

	MyLogger::log()->info("[Chi2Algorithm] ***************************** ");
	MyLogger::log()->info("[Chi2Algorithm] >> Normalize image ");

    t1 = omp_get_wtime();
	Chi2Lib::normalizeImage(&_data);
    t2 = omp_get_wtime();
    time_normalize += (t2-t1);

	MyLogger::log()->info("[Chi2Algorithm] ***************************** ");
	MyLogger::log()->info("[Chi2Algorithm] >> Generate Chi2 image ");
	MyMatrix<double> kernel = Chi2Lib::generateKernel(ss, os, _d, _w);
	MyMatrix<double> chi_img(_data.sX()+kernel.sX()-1, _data.sY()+kernel.sY()-1);
    
    //msgenter("comenzando a medir FFT\n", 0);
    t1 = omp_get_wtime();
	Chi2LibFFTW::getChiImage(&kernel, &_data, &chi_img);
    t2 = omp_get_wtime();
    time_fft += (t2-t1);
    //msgenter(": %f secs\n", t2-t1);

	MyLogger::log()->info("[Chi2Algorithm] ***************************** ");
	MyLogger::log()->info("[Chi2Algorithm] >> Obtain peaks of Chi2 Image ");
	unsigned int threshold = 5, minsep = _minsep, mindistance = 5;

    t1 = omp_get_wtime();
	vector<MyPeak> peaks = Chi2Lib::getPeaks(&chi_img, threshold, mindistance, minsep, use_threads);
    t2 = omp_get_wtime();
    time_getpeaks += (t2-t1);

	MyLogger::log()->info("[Chi2Algorithm] ***************************** ");
	MyLogger::log()->info("[Chi2Algorithm] >> Generate Auxiliary Matrix ");
	MyMatrix<double> grid_x(_data.sX(), _data.sY());
	MyMatrix<double> grid_y(_data.sX(), _data.sY());
	MyMatrix<int> over(_data.sX(), _data.sY());
    t1 = omp_get_wtime();
	Chi2Lib::generateGrid(&peaks, os, &_data, &grid_x, &grid_y, &over);
    t2 = omp_get_wtime();
    time_gengrid += (t2-t1);

	MyLogger::log()->info("[Chi2Algorithm] ***************************** ");
	MyLogger::log()->info("[Chi2Algorithm] >> Compute Chi2 Difference ");
	MyMatrix<double> chi2diff(_data.sX(), _data.sY());

    t1 = omp_get_wtime();
	double currentChi2Error = Chi2Lib::computeDifference(&_data, &grid_x, &grid_y, _d, _w, &chi2diff, use_threads);
    t2 = omp_get_wtime();
    time_chi2 += (t2-t1);

	MyLogger::log()->info("[Chi2Algorithm] ***************************** ");
	MyLogger::log()->info("[Chi2Algorithm] >> Minimizing Chi2 Error ");
	unsigned int _minChi2Delta = 1;
	unsigned int iterations = 0;
	double chi2Delta = currentChi2Error;

	while( fabs(chi2Delta) > _minChi2Delta &&  iterations < _maxIterations){
        t1 = omp_get_wtime();
		Chi2Lib::newtonCenter(&over, &chi2diff, &peaks, os, _d, _w, ss);
        t2 = omp_get_wtime();
        time_newtoncenter += (t2-t1);

		for(unsigned int i=0; i < peaks.size(); ++i){
			peaks.at(i).px = peaks.at(i).px + peaks.at(i).dpx;
			peaks.at(i).py = peaks.at(i).py + peaks.at(i).dpy;

			peaks.at(i).x = (unsigned int)round(peaks.at(i).px);
			peaks.at(i).y = (unsigned int)round(peaks.at(i).py);
		}

        t1 = omp_get_wtime();
		Chi2Lib::generateGrid(&peaks, os, &_data, &grid_x, &grid_y, &over, use_threads);
        t2 = omp_get_wtime();
        time_gengrid += (t2-t1);
		chi2diff.reset(0);

        t1 = omp_get_wtime();
		double newChi2Err = Chi2Lib::computeDifference(&_data, &grid_x, &grid_y, _d, _w, &chi2diff, use_threads);
        t2 = omp_get_wtime();
        time_chi2 += (t2-t1);

		chi2Delta = currentChi2Error - newChi2Err;
		currentChi2Error = currentChi2Error-chi2Delta;
		iterations++;
	}
	MyLogger::log()->info("[Chi2HDAlgorithm] ***************************** ");
	MyLogger::log()->info("[Chi2HDAlgorithm] >> Computing Voronoi areas ");
    t1 = omp_get_wtime();
	Chi2LibQhull::addVoronoiAreas(&peaks);
    t2 = omp_get_wtime();
    time_qhull += (t2-t1);
	Chi2Lib::addState(&peaks);
	Chi2Lib::translatePeaks(&peaks, os);

    rt2 = omp_get_wtime();
    time_run = rt2 - rt1;
    time_functions = time_chi2 + time_getpeaks + time_newtoncenter + time_normalize + time_fft + time_qhull + time_gengrid;
    time_rest = time_run - time_functions;

    Ntrack = peaks.size();
    // write performance values
    fprintf(fw_times, "%4i    %4i    %8lu      %8lu    %4lu     %f      %f    %f    %f    %f    %f    %f    %f    %f    %f\n", _data.sX(), _data.sY(), Nreal, Ntrack, Nc, time_chi2, time_getpeaks, time_newtoncenter, time_normalize, time_fft, time_qhull, time_gengrid, time_functions, time_rest, time_run);
    fclose(fw_times);
    printf("\n\nchi2 L%i   Detected: %lu:\nchi2(): %f seconds\n", _data.sX(), peaks.size(), time_chi2);
    printf("getpeaks(): %f s (%f%%)\n", time_getpeaks, 100.0f*time_getpeaks/time_run);
    printf("newtoncenter(): %f s (%f%%)\n", time_newtoncenter, 100.0f*time_newtoncenter/time_run);
    printf("normalize(): %f s (%f%%)\n", time_normalize, 100.0f*time_normalize/time_run);
    printf("time_fft(): %f s (%f%%)\n", time_fft, 100.0f*time_fft/time_run);
    printf("qhull(): %f s (%f%%)\n", time_qhull, 100.0f*time_qhull/time_run);
    printf("gengrid(): %f s (%f%%)\n\n", time_gengrid, 100.0f*time_gengrid/time_run);
    printf("functions: %f s (%f%%)\n", time_functions, 100.0f*time_functions/time_run);
    printf("rest(): %f s (%f%%)\n", time_rest, 100.0f*time_rest/time_run);
    printf("run(): %f s (%f%%)\n\n", time_run, 100.0f*time_run/time_run);
    printf("Track: %f%%\n\n", 100.0f*(float)Ntrack/(float)Nreal);

    return peaks;
}
