/*
 * Chi2LibCuda.cpp
 *
 *  Created on: 18/11/2011
 *      Author: juanin
 */

#include "Chi2LibCuda.h"

cuMyArray2D Chi2LibCuda::initializeData(MyMatrix<double>* data){
	cuMyArray2D ret = CHI2HD_createArray(data->sX(), data->sY());
	ret._host_array = data->getCopy();
	CHI2HD_copyToDevice(&ret);
	return ret;
}

pair<float, float> Chi2LibCuda::getHighLow(cuMyArray2D* arr){
	MyLogger::log()->debug("[Chi2LibCuda][getHighLow] Finding Maximum and Minimum values");
	myPair mm = CHI2HD_minMax(arr);
	pair<float, float> ret;
	ret.first = mm.second;
	ret.second = mm.first;
	MyLogger::log()->debug("[Chi2LibCuda][getHighLow] Maximum and Minimum values Found: %f and %f", ret.first, ret.second);
	return ret;
}

void Chi2LibCuda::normalizeImage(cuMyArray2D* arr, double maximum, double minimum){
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
	CHI2HD_normalize(arr, min, max);
	MyLogger::log()->debug("[Chi2LibCuda][normalizeImage] Data Normalized");
}

cuMyArray2D Chi2LibCuda::generateKernel(unsigned int ss, unsigned int os, double d, double w){
	MyLogger::log()->debug("[Chi2LibCuda][generateKernel] Building kernel with ss=%i; os=%i; d=%f; w=%f",ss,os,d,w);
	cuMyArray2D ret = CHI2HD_gen_kernel(ss, os, (float) d, (float) w);
	MyLogger::log()->debug("[Chi2LibCuda][generateKernel] Kernel successfuly built");

	return ret;
}

