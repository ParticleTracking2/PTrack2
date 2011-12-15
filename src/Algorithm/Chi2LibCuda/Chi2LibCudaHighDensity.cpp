/*
 * Chi2LibCudaHighDensity.cpp
 *
 *  Created on: 13/12/2011
 *      Author: juanin
 */

#include "Chi2LibCudaHighDensity.h"

void Chi2LibCudaHighDensity::generateScaledImage(cuMyMatrix *diff, cuMyMatrix *out){
	MyLogger::log()->debug("[Chi2LibCudaHighDensity][generateScaledImage] Scaling ");
	Chi2LibcuHighDensity::scaleImage(diff, out);

	MyLogger::log()->debug("[Chi2LibCudaHighDensity][generateScaledImage] Finding Maximum and Minimum ");
	pair<float, float> maxMin = Chi2LibCuda::getHighLow(out);
	float maxval = maxMin.first;

	MyLogger::log()->debug("[Chi2LibCudaHighDensity][generateScaledImage] Inverting ");
	Chi2LibcuHighDensity::invertImage(out, maxval);

	MyLogger::log()->debug("[Chi2LibCudaHighDensity][generateScaledImage] Normalizing ");
	Chi2LibCuda::normalizeImage(out, maxMin.first, maxMin.second);

	MyLogger::log()->debug("[Chi2LibCudaHighDensity][generateScaledImage] Generation complete ");
}

unsigned int Chi2LibCudaHighDensity::checkInsidePeaks(cuMyPeakArray *old_peaks, cuMyPeakArray *new_peaks, cuMyMatrix *img, unsigned int os){
	unsigned int totalinside = 0;
	MyLogger::log()->debug("[Chi2LibCudaHighDensity][checkInsidePeaks] Scaling ");
	totalinside = Chi2LibcuHighDensity::checkInsidePeaks(old_peaks, new_peaks, img, os);
	MyLogger::log()->debug("[Chi2LibCudaHighDensity][checkInsidePeaks] Total peaks inside image %i of %i ",new_peaks->size(), totalinside);
	new_peaks->deallocate();

	return totalinside;
}

void Chi2LibCudaHighDensity::filterPeaksOutside(cuMyPeakArray *peaks, cuMyMatrix *img, unsigned int os){
	MyLogger::log()->debug("[Chi2LibCudaHighDensity][filterPeaksOutside] Filtering peaks outside image ");
	Chi2LibcuHighDensity::filterPeaksOutside(peaks, img, os);
	MyLogger::log()->debug("[Chi2LibCudaHighDensity][filterPeaksOutside] Filtering peaks outside image ");
}

pair<double, double> Chi2LibCudaHighDensity::gaussianFit(cuMyPeakArray *peaks, cuMyMatrix *img, unsigned int ss){
	MyLogger::log()->debug("[Chi2LibCudaHighDensity][gassianFit] Calculating MU and SIGMA ");
	pair<double, double> ret = Chi2LibcuHighDensity::gaussianFit(peaks,img,ss);
	MyLogger::log()->debug("[Chi2LibCudaHighDensity][gassianFit] Returning MU=%f; SIGMA=%f", ret.first, ret.second);
	return ret;
}
