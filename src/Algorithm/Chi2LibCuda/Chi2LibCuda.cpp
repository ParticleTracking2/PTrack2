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

void Chi2LibCuda::normalizeImage(cuMyMatrix* arr, double maximum, double minimum){
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

cuMyMatrix Chi2LibCuda::generateKernel(unsigned int ss, unsigned int os, double d, double w){
	MyLogger::log()->debug("[Chi2LibCuda][generateKernel] Building kernel with ss=%i; os=%i; d=%f; w=%f",ss,os,d,w);
	cuMyMatrix ret = Chi2Libcu::gen_kernel(ss, os, (float) d, (float) w);
	MyLogger::log()->debug("[Chi2LibCuda][generateKernel] Kernel successfuly built");
	return ret;
}

cuMyPeakArray Chi2LibCuda::convertPeaks(vector<MyPeak>* peaks){
	cuMyPeakArray ret;
	ret._host_array = (cuMyPeak*)malloc(peaks->size()*sizeof(cuMyPeak));
	ret.size = peaks->size();

	for(unsigned int i=0; i < peaks->size(); ++i){
		ret._host_array[i].x = peaks->at(i).x;
		ret._host_array[i].y = peaks->at(i).y;
		ret._host_array[i].chi_intensity = peaks->at(i).intensity;
	}

	return ret;
}

cuMyPeakArray Chi2LibCuda::getPeaks(cuMyMatrix* arr, int threshold, int mindistance, int minsep){
	MyLogger::log()->debug("[Chi2LibCuda][getPeaks] Getting Image peaks");
//	CHI2HD_getPeaks(arr,threshold, mindistance, minsep);

	MyLogger::log()->debug("[Chi2LibCuda][getPeaks] Copying to Host");
	arr->copyToHost();
	MyLogger::log()->debug("[Chi2LibCuda][getPeaks] Copying to MyMatrix");
	MyMatrix<double> chi_img(arr->hostPointer(), arr->sizeX(), arr->sizeY(), true);
	vector<MyPeak> peaks = Chi2Lib::getPeaks(&chi_img, threshold, mindistance, minsep, true);

	cuMyPeakArray ret = convertPeaks(&peaks);
	MyLogger::log()->debug("[Chi2LibCuda][getPeaks] Peaks Detected %i of %i", peaks.size(), arr->size());

	return ret;
}
