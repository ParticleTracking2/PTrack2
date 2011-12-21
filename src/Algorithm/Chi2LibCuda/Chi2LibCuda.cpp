/*
 * Chi2LibCuda.cpp
 *
 *  Created on: 18/11/2011
 *      Author: juanin
 */

#include "Chi2LibCuda.h"

cuMyMatrix Chi2LibCuda::initializeData(MyMatrix<double>* data){
	MyLogger::log()->debug("[Chi2LibCuda][initializeData] Getting 1 Dimension Copy of MyMatrix");
	float * copyedData = data->getCopy();
	MyLogger::log()->debug("[Chi2LibCuda][initializeData] 1 Dimension copy aquired");
	MyLogger::log()->debug("[Chi2LibCuda][initializeData] Creating cuMyMatrix");
	cuMyMatrix ret(copyedData, data->sX(), data->sY());
	MyLogger::log()->debug("[Chi2LibCuda][initializeData] cuMyMatrix successfully");
	free(copyedData);
	return ret;
}

pair<float, float> Chi2LibCuda::getHighLow(cuMyMatrix* arr){
	MyLogger::log()->debug("[Chi2LibCuda][getHighLow] Finding Maximum and Minimum values");
	pair<float, float> ret = Chi2Libcu::minMax(arr);
	float tmp = ret.first;
	ret.first = ret.second;
	ret.second = tmp;
	MyLogger::log()->debug("[Chi2LibCuda][getHighLow] Maximum and Minimum values Found: %f and %f", ret.first, ret.second);
	return ret;
}

void Chi2LibCuda::normalizeImage(cuMyMatrix* arr, float maximum, float minimum){
	MyLogger::log()->debug("[Chi2LibCuda][normalizeImage] Normalizing data");
	float min, max;
	if(maximum == -1 && minimum == -1){
		pair<float, float> maxMin = getHighLow(arr);
		min = maxMin.second;
		max = maxMin.first;
	}else{
		min = minimum;
		max = maximum;
	}
	Chi2Libcu::normalize(arr, min, max);
	MyLogger::log()->debug("[Chi2LibCuda][normalizeImage] Data Normalized");
}

cuMyMatrix Chi2LibCuda::generateKernel(unsigned int ss, unsigned int os, float d, float w){
	MyLogger::log()->debug("[Chi2LibCuda][generateKernel] Building kernel with ss=%i; os=%i; d=%f; w=%f",ss,os,d,w);
	cuMyMatrix ret = Chi2Libcu::gen_kernel(ss, os, d, w);
	MyLogger::log()->debug("[Chi2LibCuda][generateKernel] Kernel successfuly built");
	return ret;
}

cuMyPeakArray Chi2LibCuda::convertPeaks(vector<MyPeak>* peaks){
	cuMyPeakArray ret(peaks->size());
	ret.copyToHost();

	for(unsigned int i=0; i < peaks->size(); ++i){
		cuMyPeak tmp;
		tmp.x = peaks->at(i).x;
		tmp.y = peaks->at(i).y;
		tmp.chi_intensity = peaks->at(i).intensity;
		tmp.fx = peaks->at(i).x;
		tmp.fy = peaks->at(i).y;
		tmp.dfx = 0;
		tmp.dfy = 0;
		tmp.solid = false;
		tmp.valid = true;
		tmp.vor_area = 0;
		ret.atHost(i) = tmp;
	}

	return ret;
}

cuMyPeakArray Chi2LibCuda::getPeaks(cuMyMatrix* arr, int threshold, int mindistance, int minsep, bool validate){
	MyLogger::log()->debug("[Chi2LibCuda][getPeaks] Getting Image peaks");
	cuMyPeakArray ret = Chi2Libcu::getPeaks(arr, threshold, mindistance, minsep);
	if(validate){
		MyLogger::log()->debug("[Chi2LibCuda][getPeaks] Validating");
		Chi2Libcu::validatePeaks(&ret, mindistance);
	}
	MyLogger::log()->debug("[Chi2LibCuda][getPeaks] Peaks Detected %i of %i", ret.size(), arr->size());
	return ret;
}

vector<MyPeak> Chi2LibCuda::convert(cuMyPeakArray* peaks){
	MyLogger::log()->debug("[Chi2LibCuda][convert] Converting Peaks to original format");
	vector<MyPeak> ret;
	ret.reserve(peaks->size());
	peaks->copyToHost();

	cuMyPeak* hpeaks = peaks->hostPointer();
	for(unsigned int i=0; i< peaks->size(); ++i){
		MyPeak tmp(hpeaks[i].x, hpeaks[i].y, hpeaks[i].chi_intensity);
		tmp.px = hpeaks[i].fx;
		tmp.py = hpeaks[i].fy;
		tmp.dpx = hpeaks[i].dfx;
		tmp.dpy = hpeaks[i].dfy;
		tmp.solid = hpeaks[i].solid;
		tmp.vor_area = hpeaks[i].vor_area;
		ret.push_back(tmp);
	}
	MyLogger::log()->debug("[Chi2LibCuda][convert] Peaks Converted, Total Valids : %i", ret.size());
	return ret;
}

void Chi2LibCuda::generateGrid(cuMyPeakArray* peaks, unsigned int shift, cuMyMatrix* grid_x, cuMyMatrix* grid_y, cuMyMatrixi* over){
	MyLogger::log()->debug("[Chi2LibCuda][generateGrid] Generating Auxiliary Matrix");
	MyLogger::log()->debug("[Chi2LibCuda][generateGrid] Grid Size: %ix%i", grid_x->sizeX(), grid_x->sizeY());
//	Chi2Libcu::generateGrid(peaks, shift, grid_x, grid_y, over);
	unsigned int half=(shift+2);
	unsigned int counter = 0;
	int currentX, currentY;
	double currentDistance = 0.0;
	double currentDistanceAux = 0.0;
	float maxval = grid_x->sizeX() > grid_x->sizeY() ? grid_x->sizeX() : grid_x->sizeY();

	grid_x->reset(maxval);
	grid_y->reset(maxval);
	over->reset(0);

	peaks->copyToHost();
	grid_x->copyToHost();
	grid_y->copyToHost();
	over->copyToHost();

	if(peaks->size() != 0)
	for(int npks = peaks->size()-1; npks >= 0; npks--){
		for(unsigned int localX=0; localX < 2*half+1; ++localX)
			for(unsigned int localY=0; localY < 2*half+1; ++localY){
				cuMyPeak currentPeak = peaks->getHostValue(npks);
//				MyLogger::log()->debug("[Chi2LibCuda][generateGrid] Peak[i]: fx=%f; fy=%f", npks, currentPeak.fx, currentPeak.fy);
				currentX = (int)round(currentPeak.fx) - shift + (localX - half);
				currentY = (int)round(currentPeak.fy) - shift + (localY - half);

				if( 0 <= currentX && currentX < (int)grid_x->sizeX() && 0 <= currentY && currentY < (int)grid_x->sizeY() ){
					currentDistance =
							sqrt(grid_x->getValueHost(currentX, currentY)*grid_x->getValueHost(currentX, currentY)
								+ grid_y->getValueHost(currentX, currentY)*grid_y->getValueHost(currentX, currentY));

					currentDistanceAux =
							sqrt(1.0*(1.0*localX-half+currentPeak.x - currentPeak.fx)*(1.0*localX-half+currentPeak.x - currentPeak.fx) +
								 1.0*(1.0*localY-half+currentPeak.y - currentPeak.fy)*(1.0*localY-half+currentPeak.y - currentPeak.fy));

					if(currentDistance >= currentDistanceAux){
						over->atHost(currentX, currentY) = npks+1;
						grid_x->atHost(currentX, currentY) = (1.0*localX-half+currentPeak.x)-currentPeak.fx;
						grid_y->atHost(currentX, currentY) = (1.0*localY-half+currentPeak.y)-currentPeak.fy;
						counter++;
					}
				}

			}
	}
	grid_x->copyToDevice();
	grid_y->copyToDevice();
	over->copyToDevice();

	MyLogger::log()->debug("[Chi2LibCuda][generateGrid] Generating Auxiliary Matrix Complete, Counter =%i", counter);
}

float Chi2LibCuda::computeDifference(cuMyMatrix *img, cuMyMatrix *grid_x, cuMyMatrix *grid_y, float d, float w, cuMyMatrix *diffout){
	MyLogger::log()->debug("[Chi2LibCuda][computeDifference] Computing Chi2Difference");
	float err = Chi2Libcu::computeDifference(img, grid_x, grid_y, d, w, diffout);
	MyLogger::log()->debug("[Chi2LibCuda][computeDifference] Chi2Difference Computed: Chi2Error = %f", err);
	return err;
}

void Chi2LibCuda::newtonCenter(cuMyMatrixi *over, cuMyMatrix *diff, cuMyPeakArray *peaks, int shift, double D, double w, double dp, double maxdr){
	MyLogger::log()->debug("[Chi2LibCuda][newtonCenter] Calculating Newton Center");
	Chi2Libcu::newtonCenter(over, diff, peaks, shift, (float)D, (float)w, (float)dp, (float)maxdr);
	MyLogger::log()->debug("[Chi2LibCuda][newtonCenter] Calculation Complete");
}

void Chi2LibCuda::translatePeaks(cuMyPeakArray *peaks, unsigned int ss){
	MyLogger::log()->info("[Chi2LibCuda][transformPeaks] Transforming peaks");
	peaks->copyToHost();
	for(unsigned int i=0; i < peaks->size(); ++i){
		peaks->atHost(i).fy = peaks->getHostValue(i).fy - ss+1;
		peaks->atHost(i).fx = peaks->getHostValue(i).fx - ss+1;
	}
	peaks->copyToDevice();
	MyLogger::log()->info("[Chi2LibCuda][transformPeaks] Peaks transformed");
}

void Chi2LibCuda::addState(cuMyPeakArray *peaks, float vor_areaSL){
	MyLogger::log()->info("[Chi2LibCuda][addState] Transforming peaks");
	peaks->copyToHost();
	for(unsigned int i=0; i < peaks->size(); ++i){
		if(peaks->getHostValue(i).vor_area < vor_areaSL && peaks->getHostValue(i).vor_area > 0)
			peaks->atHost(i).solid = true;
		else
			peaks->atHost(i).solid = false;
	}
	peaks->copyToDevice();
	MyLogger::log()->info("[Chi2LibCuda][addState] Peaks transformed");
}
