/*
 * Chi2LibCuda.cpp
 *
 *  Created on: 18/11/2011
 *      Author: juanin
 */

#include "Chi2LibCuda.h"

cuMyMatrix Chi2LibCuda::initializeData(MyMatrix<double>* data){
	float * copyedData = data->getCopy();
	cuMyMatrix ret(copyedData, data->sX(), data->sY());
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
		tmp.img_intensity = 0;
		tmp.solid = false;
		tmp.valid = true;
		tmp.vor_area = 0;
		ret.atHost(i) = tmp;
	}

	return ret;
}

cuMyPeakArray Chi2LibCuda::getPeaks(cuMyMatrix* arr, int threshold, int mindistance, int minsep){
	MyLogger::log()->debug("[Chi2LibCuda][getPeaks] Getting Image peaks");
	cuMyPeakArray ret = Chi2Libcu::getPeaks(arr, threshold, mindistance, minsep);
	MyLogger::log()->debug("[Chi2LibCuda][getPeaks] Valid Peaks Detected %i of %i", ret.size(), arr->size());
	return ret;
}

vector<MyPeak> Chi2LibCuda::convert(cuMyPeakArray* peaks){
	MyLogger::log()->debug("[Chi2LibCuda][convert] Converting Peaks to original format");
	vector<MyPeak> ret;
	ret.reserve(peaks->size());
	peaks->copyToHost();

	cuMyPeak* hpeaks = peaks->hostPointer();
	for(unsigned int i=0; i< peaks->size(); ++i){
		if(hpeaks[i].valid){
			MyPeak tmp(hpeaks[i].x, hpeaks[i].y, hpeaks[i].chi_intensity);
			ret.push_back(tmp);
		}
	}
	MyLogger::log()->debug("[Chi2LibCuda][convert] Peaks Converted, Total Valids : %i", ret.size());
	return ret;
}

void Chi2LibCuda::generateGrid(cuMyPeakArray* peaks, unsigned int shift, cuMyMatrix* grid_x, cuMyMatrix* grid_y, cuMyMatrixi* over){
	MyLogger::log()->debug("[Chi2LibCuda][generateGrid] Generating Auxiliary Matrix");
	MyLogger::log()->debug("[Chi2LibCuda][generateGrid] Grid Size: %ix%i", grid_x->sizeX(), grid_x->sizeY());
	Chi2Libcu::generateGrid(peaks, shift, grid_x, grid_y, over);
	MyLogger::log()->debug("[Chi2LibCuda][generateGrid] Generating Auxiliary Matrix Complete");
}

float Chi2LibCuda::computeDifference(cuMyMatrix *img, cuMyMatrix *grid_x, cuMyMatrix *grid_y, float d, float w, cuMyMatrix *diffout){
	MyLogger::log()->debug("[Chi2LibCuda][computeDifference] Computing Chi2Difference");
	float err = Chi2Libcu::computeDifference(img, grid_x, grid_y, d, w, diffout);
	MyLogger::log()->debug("[Chi2LibCuda][computeDifference] Chi2Difference Computed: Chi2Error = %f", err);
	return err;
}

void Chi2LibCuda::translatePeaks(vector<MyPeak> *peaks, unsigned int ss){
	MyLogger::log()->info("[Chi2LibCuda][transformPeaks] Transforming peaks");
	for(unsigned int i=0; i < peaks->size(); ++i){
		peaks->at(i).py = peaks->at(i).py - ss+1;
		peaks->at(i).px = peaks->at(i).px - ss+1;
	}
	MyLogger::log()->info("[Chi2LibCuda][transformPeaks] Peaks transformed");
}
