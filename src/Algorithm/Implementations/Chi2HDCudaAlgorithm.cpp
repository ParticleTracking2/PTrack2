/*
 * Chi2HDCudaAlgorithm.cpp
 *
 *  Created on: 15-11-2011
 *      Author: ptrack
 */
#ifdef CHI2CUDA
#include "Chi2HDCudaAlgorithm.h"
#include <omp.h>

ArgObj Chi2HDCudaAlgorithm::myArgs(){
	ArgObj chi2hdcuda;
	chi2hdcuda.type = Chi2HDCuda_Algorithm;
	chi2hdcuda.argkey = "chi2hdcuda";
	chi2hdcuda.description = "Convolution based least-squares fitting for High density particle systems. Using CUDA Technology.";
	chi2hdcuda.example = "chi2hdcuda -i MyImage.tif -d 9.87 -w 1.84";

	/* Parametros aceptables */
	KeyTreat img; img.key = "-i"; img.description = "Image to read.";
	img.treat.push_back(Require_Treat);
	img.treat.push_back(Followed_String_Treat);
	chi2hdcuda.keys_treats.push_back(img);

	KeyTreat d; d.key = "-d"; d.description = "Diameter of an ideal particle. (Default = 9.87).";
	d.treat.push_back(Followed_Double_Treat);
	chi2hdcuda.keys_treats.push_back(d);

	KeyTreat w; w.key = "-w"; w.description = "Value of how sharply the ideal particle is viewed (Focus). (Default = 1.84).";
	w.treat.push_back(Followed_Double_Treat);
	chi2hdcuda.keys_treats.push_back(w);

	KeyTreat minsep; minsep.key = "-minsep"; minsep.description = "Minimal Separations between peaks. (Default 1)";
	minsep.treat.push_back(Followed_Int_Treat);
	chi2hdcuda.keys_treats.push_back(minsep);
	
	KeyTreat cut; cut.key = "-cut"; cut.description = "Crop image by each side (in pixels).";
	cut.treat.push_back(Followed_Int_Treat);
	chi2hdcuda.keys_treats.push_back(cut);

	KeyTreat maxchi2miniter; maxchi2miniter.key = "-maxchi2miniter"; maxchi2miniter.description = "Limit the iteration for minimizing Chi2Error (Default = 5).";
	maxchi2miniter.treat.push_back(Followed_Int_Treat);
	chi2hdcuda.keys_treats.push_back(maxchi2miniter);

	KeyTreat chi_cut; chi_cut.key = "-chicut"; chi_cut.description = "Minimal intensity of the convolution peaks to be detected.";
	chi_cut.treat.push_back(Followed_Double_Treat);
	chi2hdcuda.keys_treats.push_back(chi_cut);

	KeyTreat vor_cut; vor_cut.key = "-vorcut"; vor_cut.description = "Minimal Voronoi area acceptable of peak to be considered as peak.";
	vor_cut.treat.push_back(Followed_Double_Treat);
	chi2hdcuda.keys_treats.push_back(vor_cut);

	KeyTreat vor_sl; vor_sl.key = "-vorsl"; vor_sl.description = "Voronoi area value division of solid and liquid particle.";
	vor_sl.treat.push_back(Followed_Double_Treat);
	chi2hdcuda.keys_treats.push_back(vor_sl);

	KeyTreat filter2i; filter2i.key = "-2filteri"; filter2i.description = "Second Filter of Bad particles using Image intensity Only.";
	filter2i.treat.push_back(Followed_Double_Treat);
	chi2hdcuda.keys_treats.push_back(filter2i);

	KeyTreat filter2v; filter2v.key = "-2filterv"; filter2v.description = "Second Filter of Bad particles using Voronoi area Only.";
	filter2v.treat.push_back(Followed_Double_Treat);
	chi2hdcuda.keys_treats.push_back(filter2v);

	KeyTreat one_validation; one_validation.key = "-validateones"; one_validation.description = "Validate peaks minimum distance only Ones.";
	one_validation.treat.push_back(Exist_Treat);
	chi2hdcuda.keys_treats.push_back(one_validation);
	// -device
	KeyTreat device; device.key = "-device"; device.description = "Stablish the CUDA device to use.";
	device.treat.push_back(Followed_Int_Treat);
	chi2hdcuda.keys_treats.push_back(device);

	return chi2hdcuda;
}

void Chi2HDCudaAlgorithm::setData(ParameterContainer *pc){
	_d = 9.87;
	if(pc->existParam("-d"))
		_d = (float)pc->getParamAsDouble("-d");

	_w = 1.84;
	if(pc->existParam("-w"))
		_w = (float)pc->getParamAsDouble("-w");

	_minsep = 1;
	if(pc->existParam("-minsep"))
		_minsep = pc->getParamAsInt("-minsep");
		
	_maxIterations = 5;
	if(pc->existParam("-maxchi2miniter"))
		_maxIterations = pc->getParamAsInt("-maxchi2miniter");

	_chi_cut = 2;
	if(pc->existParam("-chicut"))
		_chi_cut = (float)pc->getParamAsDouble("-chicut");

	_vor_thresh = 50.0;
	if(pc->existParam("-vorcut"))
		_vor_thresh = (float)pc->getParamAsDouble("-vorcut");

	_vor_areaSL = 75.0;
	if(pc->existParam("-vorsl"))
		_vor_areaSL = (float)pc->getParamAsDouble("-vorsl");

	_FilterI = 1.0;
	_secondFilterI = false;
	if(pc->existParam("-2filteri")){
		_secondFilterI = true;
		_FilterI = pc->getParamAsDouble("-2filteri");
	}

	_FilterV = 50.0;
	_secondFilterV = false;
	if(pc->existParam("-2filterv")){
		_secondFilterV = true;
		_FilterV = pc->getParamAsDouble("-2filterv");
	}

	_cudaDev = 0;
	_cuda = false;
	if(pc->existParam("-device")){
		_cuda = true;
		_cudaDev = pc->getParamAsInt("-device");
	}

	if(pc->existParam("-validateones"))
		_validateOnes = true;
	else
		_validateOnes = false;

	if(_cuda){
		Chi2Libcu::setDevice(_cudaDev);
	}
	if(pc->existParam("-cut"))
		cuImg = MyImageFactory::makeCuRawImgFromFile(pc->getParamAsString("-i"), pc->getParamAsInt("-cut"));
	else
		cuImg = MyImageFactory::makeCuRawImgFromFile(pc->getParamAsString("-i"));



    printf("scanning string: %s\n", pc->getParamAsString("-i").c_str());
    sscanf(pc->getParamAsString("-i").c_str(), "%[^_]_fD%f_A%i_B%i_L%i_N%i_NC%i_d%f.tif", prefix, &fD, &A, &B, &L, &Nreal, &Nc, &density);
    printf("parsed:\nprefix:%s\nfD:%f\nA:%i\nB:%i\nL:%i\nN:%i\nNC:%i\nd:%f\n", prefix, fD, A, B, L, Nreal, Nc, density);

}

vector<MyPeak> Chi2HDCudaAlgorithm::run(){
    double t1, t2, rt1, rt2;
    FILE *fw_times = fopen("chi2HDCuda_times.dat", "a");
    float time_chi2 = 0.0f, time_getpeaks = 0.0f, time_newtoncenter = 0.0f, time_normalize = 0.0f, time_fft = 0.0f, time_qhull = 0.0f, time_gengrid = 0.0f, time_functions = 0.0f, time_rest = 0.0f, time_run = 0.0f;
    rt1 = omp_get_wtime();

	MyLogger::log()->notice("[Chi2HDCudaAlgorithm] Running Chi2HD CUDA Algorithm");

	DeviceProps props = Chi2Libcu::getProps();
	MyLogger::log()->notice("[Chi2HDCudaAlgorithm] ***************************** ");
	MyLogger::log()->notice("[Chi2HDCudaAlgorithm] Setting CUDA Device %i = %s", props.device, props.name);

	int ss = 2*floor(_d/2 + 4*_w/2)-1;
	int os = (ss-1)/2;

	MyLogger::log()->info("[Chi2HDCudaAlgorithm] ***************************** ");
	MyLogger::log()->info("[Chi2HDCudaAlgorithm] >> Initializing Device Data ");

	MyLogger::log()->info("[Chi2HDCudaAlgorithm] ***************************** ");
	MyLogger::log()->info("[Chi2HDCudaAlgorithm] >> Normalize image ");
	pair<float, float> hilo = Chi2LibCuda::getHighLow(&cuImg);
    // MEASURE
    t1 = omp_get_wtime();
	Chi2LibCuda::normalizeImage(&cuImg, hilo.first, hilo.second);
    t2 = omp_get_wtime();
    time_normalize += (t2-t1);

	MyLogger::log()->info("[Chi2HDCudaAlgorithm] ***************************** ");
	MyLogger::log()->info("[Chi2HDCudaAlgorithm] >> Generate Chi2 image ");
	cuMyMatrix cuKernel = Chi2LibCuda::generateKernel(ss, os, _d, _w);
	cuMyMatrix cu_chi_img(cuImg.sizeX()+cuKernel.sizeX()-1, cuImg.sizeY()+cuKernel.sizeY()-1);
    t1 = omp_get_wtime();
	Chi2LibCudaFFT::getChiImage(&cuKernel, &cuImg, &cu_chi_img);
    t2 = omp_get_wtime();
    time_fft += (t2-t1);

	MyLogger::log()->info("[Chi2HDCudaAlgorithm] ***************************** ");
	MyLogger::log()->info("[Chi2HDCudaAlgorithm] >> Obtain peaks of Chi2 Image ");
	unsigned int threshold = 5, minsep = _minsep, mindistance = 5;
    // MEASURE
    t1 = omp_get_wtime();
	cuMyPeakArray peaks = Chi2LibCuda::getPeaks(&cu_chi_img, threshold, mindistance, minsep, !_validateOnes);
    t2 = omp_get_wtime();
    time_getpeaks += (t2-t1);

	MyLogger::log()->info("[Chi2HDCudaAlgorithm] ***************************** ");
	MyLogger::log()->info("[Chi2HDCudaAlgorithm] >> Generate Auxiliary Matrix ");
	MyLogger::log()->debug("[Chi2HDCudaAlgorithm] >> Allocating %ix%i", cuImg.sizeX(), cuImg.sizeY());
	cuMyMatrix grid_x(cuImg.sizeX(), cuImg.sizeY());
	cuMyMatrix grid_y(cuImg.sizeX(), cuImg.sizeY());
	cuMyMatrixi over(cuImg.sizeX(), cuImg.sizeY());
	MyLogger::log()->debug("[Chi2HDCudaAlgorithm] >> Allocation Complete ");
    t1 = omp_get_wtime();
	Chi2LibCuda::generateGrid(&peaks, os, &grid_x, &grid_y, &over);
    t2 = omp_get_wtime();
    time_gengrid += (t2-t1);
	FileUtils::writeToFileM(&grid_x, "grid_x-cuda.txt");
	FileUtils::writeToFileM(&grid_y, "grid_y-cuda.txt");
	FileUtils::writeToFileM(&over, "over-cuda.txt");

	MyLogger::log()->info("[Chi2HDCudaAlgorithm] ***************************** ");
	MyLogger::log()->info("[Chi2HDCudaAlgorithm] >> Compute Chi2 Difference ");
	cuMyMatrix chi2diff(cuImg.sizeX(), cuImg.sizeY());
    // MEASURE
    t1 = omp_get_wtime();
	float currentChi2Error = Chi2LibCuda::computeDifference(&cuImg, &grid_x, &grid_y, _d, _w, &chi2diff);
    t2 = omp_get_wtime();
    time_chi2 += (t2-t1);

	MyLogger::log()->info("[Chi2HDCudaAlgorithm] ***************************** ");
	MyLogger::log()->info("[Chi2HDCudaAlgorithm] >> Add missed points ");

	unsigned int total_found = 0;
	cuMyMatrix normaldata_chi(cuImg.sizeX(), cuImg.sizeY());

	unsigned int _maxFirstIterations = 10, iterations = 0;
	while(iterations <= _maxFirstIterations){
		MyLogger::log()->info("[Chi2HDCudaAlgorithm] >> Generating Scaled Image ");
        // MEASURE
		time_normalize += Chi2LibCudaHighDensity::generateScaledImage(&chi2diff, &normaldata_chi);

		MyLogger::log()->info("[Chi2HDCudaAlgorithm] >> Obtaining new CHi2 Image ");
        t1 = omp_get_wtime();
		Chi2LibCudaFFT::getChiImage(&cuKernel, &normaldata_chi, &cu_chi_img);
        t2 = omp_get_wtime();
        time_fft += (t2-t1);

		MyLogger::log()->info("[Chi2HDCudaAlgorithm] >> Obtaining new Peaks ");
        // MEASURE
        t1 = omp_get_wtime();
		cuMyPeakArray new_peaks = Chi2LibCuda::getPeaks(&cu_chi_img, _chi_cut, mindistance, minsep, !_validateOnes);
        t2 = omp_get_wtime();
        time_getpeaks += (t2-t1);

		unsigned int old_size = peaks.size();
		MyLogger::log()->info("[Chi2HDCudaAlgorithm] >> Checking inside image peaks ");
		unsigned int found = Chi2LibCudaHighDensity::checkInsidePeaks(&peaks, &new_peaks, &cuImg, os);
		total_found += found;

		if(found <= 0)
			break;

		MyLogger::log()->info("[Chi2HDCudaAlgorithm] >> Generating Auxiliary Matrix ");
        t1 = omp_get_wtime();
		Chi2LibCuda::generateGrid(&peaks, os, &grid_x, &grid_y, &over);
        t2 = omp_get_wtime();
        time_gengrid += (t2-t1);

		MyLogger::log()->info("[Chi2HDCudaAlgorithm] >> Computing Chi2 Difference ");
        // MEASURE
        t1 = omp_get_wtime();
		currentChi2Error = Chi2LibCuda::computeDifference(&cuImg, &grid_x, &grid_y, _d, _w, &chi2diff);
        t2 = omp_get_wtime();
        time_chi2 += (t2-t1);

		MyLogger::log()->info("[Chi2HDAlgorithm] >> Original No of Points: %i, +%i; Total Found = %i", old_size, found, total_found);

		iterations++;
	}
	peaks.sortByChiIntensity();
    t1 = omp_get_wtime();
	Chi2LibCudaFFTCache::eraseAll();
    t2 = omp_get_wtime();
    time_fft += (t2-t1);
	normaldata_chi.deallocate();

	MyLogger::log()->info("[Chi2HDCudaAlgorithm] ***************************** ");
	MyLogger::log()->info("[Chi2HDCudaAlgorithm] >> Recompute Auxiliary matrix and Chi2 Difference ");
	MyLogger::log()->debug("[Chi2HDCudaAlgorithm] >> Recompute Auxiliary matrix");
    t1 = omp_get_wtime();
	Chi2LibCuda::generateGrid(&peaks, os, &grid_x, &grid_y, &over);
    t2 = omp_get_wtime();
    time_gengrid += (t2-t1);

	MyLogger::log()->info("[Chi2HDCudaAlgorithm] >> Recompute Chi2 Difference");
    // MEASURE
    t1 = omp_get_wtime();
	currentChi2Error = Chi2LibCuda::computeDifference(&cuImg, &grid_x, &grid_y, _d, _w, &chi2diff);
    t2 = omp_get_wtime();
    time_chi2 += (t2-t1);

	MyLogger::log()->info("[Chi2HDCudaAlgorithm] ***************************** ");
	MyLogger::log()->info("[Chi2HDCudaAlgorithm] >> Minimizing Chi2 Error ");
	unsigned int _minChi2Delta = 1;
	iterations = 0;
	double chi2Delta = currentChi2Error;

	while( fabs(chi2Delta) > _minChi2Delta &&  iterations < _maxIterations){
        // MEASURE
        t1 = omp_get_wtime();
		Chi2LibCuda::newtonCenter(&over, &chi2diff, &peaks, os, _d, _w, ss, 20.0);
        t2 = omp_get_wtime();
        time_newtoncenter += (t2-t1);
		peaks.includeDeltas();

        t1 = omp_get_wtime();
		Chi2LibCuda::generateGrid(&peaks, os, &grid_x, &grid_y, &over);
        t2 = omp_get_wtime();
        time_gengrid += (t2-t1);
		chi2diff.reset(0);

        // MEASURE
        t1 = omp_get_wtime();
		double newChi2Err = Chi2LibCuda::computeDifference(&cuImg, &grid_x, &grid_y, _d, _w, &chi2diff);
        t2 = omp_get_wtime();
        time_chi2 += (t2-t1);
		MyLogger::log()->info("[Chi2HDAlgorithm] >> Chi2Error: %f", newChi2Err);
		chi2Delta = currentChi2Error - newChi2Err;
		currentChi2Error = currentChi2Error-chi2Delta;
		iterations++;
	}

	if(_validateOnes){
		MyLogger::log()->info("[Chi2HDCudaAlgorithm] ***************************** ");
		MyLogger::log()->info("[Chi2HDCudaAlgorithm] Validating Peaks obtained so far ");
		unsigned int old_size = peaks.size();
		Chi2Libcu::validatePeaks(&peaks, mindistance);
		MyLogger::log()->info("[Chi2HDCudaAlgorithm] Peaks deleted : %i, New Peaks Size : %i ", old_size-peaks.size(), peaks.size());
	}

	MyLogger::log()->info("[Chi2HDCudaAlgorithm] ***************************** ");
	MyLogger::log()->info("[Chi2HDCudaAlgorithm] >> Checking particles by pixel intensity and voronoi area Tom's algorithm ");

	MyLogger::log()->info("[Chi2HDCudaAlgorithm] >> Remove outside image peaks");
	Chi2LibCudaHighDensity::filterPeaksOutside(&peaks, &cuImg, os);

	MyLogger::log()->info("[Chi2HDCudaAlgorithm] >> Apply Gaussian Fit ");
    //t1 = omp_get_wtime();
	pair<double,double> mypair = Chi2LibCudaHighDensity::gaussianFit(&peaks,&cuImg, os);
    //t2 = omp_get_wtime();
    //printf("gaussian = %f\n", t2-t1);
	double mu = mypair.first;
	double sigma = mypair.second;
	MyLogger::log()->info("[Chi2HDCudaAlgorithm] >> Total peaks: %i; MU=%f; SIGMA=%f", peaks.size(), mu, sigma);

	MyLogger::log()->info("[Chi2HDCudaAlgorithm] ***************************** ");
	double par_thresh = mu-3.0*sigma;

	MyLogger::log()->info("[Chi2HDCudaAlgorithm] >> Filter 'Bad' Peaks using Voronoi Area: %f - Intensity: %f", _vor_thresh, par_thresh);
	Chi2LibCudaHighDensity::removeBadPeaks(&peaks, &cuImg, _vor_thresh, par_thresh, os);

	if(_secondFilterI){
		MyLogger::log()->info("[Chi2HDCudaAlgorithm] >> Second Filter 'Bad' Peaks using intensity");
		unsigned int old_total  = peaks.size();
		Chi2LibCudaHighDensity::removeBadIntensityPeaks(&peaks, &cuImg, _FilterI, os);
		unsigned int new_total  = peaks.size();
		MyLogger::log()->info("[Chi2HDCudaAlgorithm] >> New Number of peaks: %i, Filtered :%i", new_total, (old_total - new_total));
	}

	if(_secondFilterV){
		MyLogger::log()->info("[Chi2HDCudaAlgorithm] >> Second Filter 'Bad' Peaks using Voronoi Area");
		unsigned int old_total  = peaks.size();
		Chi2LibCudaHighDensity::removeBadVoronoiPeaks(&peaks, &cuImg, _FilterV, os);
		unsigned int new_total  = peaks.size();
		MyLogger::log()->info("[Chi2HDCudaAlgorithm] >> New Number of peaks: %i, Filtered :%i", new_total, (old_total - new_total));
	}

	MyLogger::log()->info("[Chi2HDCudaAlgorithm] ***************************** ");
	MyLogger::log()->info("[Chi2HDCudaAlgorithm] >> Recompute Auxiliary matrix and Chi2 Difference");
	MyLogger::log()->info("[Chi2HDCudaAlgorithm] >> Recompute Auxiliary matrix");
    t1 = omp_get_wtime();
	Chi2LibCuda::generateGrid(&peaks, os, &grid_x, &grid_y, &over);
    t2 = omp_get_wtime();
    time_gengrid += (t2-t1);
	MyLogger::log()->info("[Chi2HDCudaAlgorithm] >> Recompute Chi2 Difference");
    // MEASURE
    t1 = omp_get_wtime();
	currentChi2Error = Chi2LibCuda::computeDifference(&cuImg, &grid_x, &grid_y, _d, _w, &chi2diff);
    t2 = omp_get_wtime();
    time_chi2 += (t2-t1);
	chi2Delta = 1000000.0;
	iterations = 0;
	MyLogger::log()->info("[Chi2HDCudaAlgorithm] ***************************** ");
	MyLogger::log()->info("[Chi2HDCudaAlgorithm] >> Minimizing Chi2 Error ");
	while( fabs(chi2Delta) > _minChi2Delta &&  iterations < _maxIterations){
        // MEASURE
        t1 = omp_get_wtime();
		Chi2LibCuda::newtonCenter(&over, &chi2diff, &peaks, os, _d, _w, ss, 20.0);
        t2 = omp_get_wtime();
        time_newtoncenter += (t2-t1);
		peaks.includeDeltas();

        t1 = omp_get_wtime();
		Chi2LibCuda::generateGrid(&peaks, os, &grid_x, &grid_y, &over);
        t2 = omp_get_wtime();
        time_gengrid += (t2-t1);
		chi2diff.reset(0);

        // MEASURE
        t1 = omp_get_wtime();
		double newChi2Err = Chi2LibCuda::computeDifference(&cuImg, &grid_x, &grid_y, _d, _w, &chi2diff);
        t2 = omp_get_wtime();
        time_chi2 += (t2-t1);
		MyLogger::log()->info("[Chi2HDAlgorithm] >> Chi2Error: %f", newChi2Err);
		chi2Delta = currentChi2Error - newChi2Err;
		currentChi2Error = currentChi2Error-chi2Delta;
		iterations++;
	}

	MyLogger::log()->info("[Chi2HDCudaAlgorithm] ***************************** ");
	MyLogger::log()->info("[Chi2HDCudaAlgorithm] >> Recomputing Voronoi areas ");
    t1 = omp_get_wtime();
	Chi2LibCudaQhull::addVoronoiAreas(&peaks);
    t2 = omp_get_wtime();
    time_qhull += (t2-t1);

	MyLogger::log()->info("[Chi2HDCudaAlgorithm] >> Translating coordenates ");
	Chi2LibCuda::translatePeaks(&peaks, os);

	MyLogger::log()->info("[Chi2HDCudaAlgorithm] >> Adding State ");
	Chi2LibCuda::addState(&peaks, _vor_areaSL);

	MyLogger::log()->info("[Chi2HDCudaAlgorithm] >> Converting Peaks to original vector : %i", peaks.size());
	vector<MyPeak> ret = Chi2LibCuda::convert(&peaks);

    // MEASURE
    rt2 = omp_get_wtime();
    time_run = rt2 - rt1;
    time_functions = time_chi2 + time_getpeaks + time_newtoncenter + time_normalize + time_fft + time_qhull + time_gengrid;
    time_rest = time_run - time_functions;

    Ntrack = peaks.size();
    // write performance values
    fprintf(fw_times, "%4i    %4i    %8i       %8lu    %4lu    %f    %f    %f    %f    %f    %f    %f    %f     %f      %f\n", cuImg.sizeX(), cuImg.sizeY(), Nreal, Ntrack, Nc,  time_chi2, time_getpeaks, time_newtoncenter, time_normalize, time_fft, time_qhull, time_gengrid, time_functions, time_rest, time_run);
    fclose(fw_times);
    printf("\n\nchi2HDCuda L%i   Detected: %i:\nchi2(): %f seconds\n", cuImg.sizeX(), peaks.size(), time_chi2);
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
	return ret;
}
#endif
