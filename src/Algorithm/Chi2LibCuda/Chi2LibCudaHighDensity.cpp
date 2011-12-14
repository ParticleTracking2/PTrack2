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
