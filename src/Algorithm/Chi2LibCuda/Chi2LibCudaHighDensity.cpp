/*
 * Chi2LibCudaHighDensity.cpp
 *
 *  Created on: 13/12/2011
 *      Author: juanin
 */

#include "Chi2LibCudaHighDensity.h"
#include "Chi2LibCudaQhull.h"

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
	MyLogger::log()->debug("[Chi2LibCudaHighDensity][gaussianFit] Calculating MU and SIGMA ");
	pair<double, double> ret = Chi2LibcuHighDensity::gaussianFit(peaks,img,ss);
	MyLogger::log()->debug("[Chi2LibCudaHighDensity][gaussianFit] Returning MU=%f; SIGMA=%f", ret.first, ret.second);
	return ret;
}

void Chi2LibCudaHighDensity::removeBadPeaks(cuMyPeakArray *peaks, cuMyMatrix *img, double vor_threshold, double par_threshold, unsigned int ss){
	MyLogger::log()->debug("[Chi2LibCudaHighDensity][removeBadPeaks] Starting removing peaks by Area < %f and Intensity < %f", vor_threshold, par_threshold);
	Chi2LibCudaQhull::addVoronoiAreas(peaks);
	img->copyToHost();

	int xx = 0, yy = 0;
	for(unsigned int i=0; i < peaks->size(); ++i){
		xx = peaks->getHostValue(i).x - ss;
		yy = peaks->getHostValue(i).y - ss;
		if(img->getValueHost(xx,yy) < par_threshold && 0 < peaks->getHostValue(i).vor_area && peaks->getHostValue(i).vor_area < vor_threshold){
			// Remove Peak element at this position
			MyLogger::log()->debug("[Chi2LibCudaHighDensity][removeBadPeaks] >> Deleting Peak: Index=%i , X=%i, Y=%i, Intensity=%f, VoronoiArea=%f", i, peaks->getHostValue(i).x, peaks->getHostValue(i).y, img->getValueHost(xx,yy), peaks->getHostValue(i).vor_area );
			peaks->atHost(i).valid = false;
		}
	}
	peaks->copyToDevice();
	peaks->keepValids();

	MyLogger::log()->debug("[Chi2LibCudaHighDensity][removeBadPeaks] Removing complete");
}

void Chi2LibCudaHighDensity::removeBadIntensityPeaks(cuMyPeakArray *peaks, cuMyMatrix *img, double par_threshold, unsigned int ss){
	MyLogger::log()->debug("[Chi2LibCudaHighDensity][removeBadIntensityPeaks] Starting removing peaks by Intensity < %f", par_threshold);

	int xx = 0, yy = 0;
	for(unsigned int i=0; i < peaks->size(); ++i){
		xx = peaks->getHostValue(i).x - ss;
		yy = peaks->getHostValue(i).y - ss;
		if(img->getValueHost(xx,yy) < par_threshold){
			// Remove Peak element at this position
			MyLogger::log()->debug("[Chi2LibCudaHighDensity][removeBadIntensityPeaks] >> Deleting Peak: Index=%i , X=%i, Y=%i, Intensity=%f", i, peaks->getHostValue(i).x, peaks->getHostValue(i).y, img->getValueHost(xx,yy));
			peaks->atHost(i).valid = false;
		}
	}
	peaks->copyToDevice();
	peaks->keepValids();

	MyLogger::log()->debug("[Chi2LibCudaHighDensity][removeBadIntensityPeaks] Removing complete");
}

void Chi2LibCudaHighDensity::removeBadVoronoiPeaks(cuMyPeakArray *peaks, cuMyMatrix *img, double vor_threshold, unsigned int ss){
	MyLogger::log()->debug("[Chi2LibCudaHighDensity][removeBadVoronoiPeaks] Starting removing peaks by Area < %f ", vor_threshold);

	int xx = 0, yy = 0;
	for(unsigned int i=0; i < peaks->size(); ++i){
		xx = peaks->getHostValue(i).x - ss;
		yy = peaks->getHostValue(i).y - ss;
		if(0 < peaks->getHostValue(i).vor_area && peaks->getHostValue(i).vor_area < vor_threshold){
			// Remove Peak element at this position
			MyLogger::log()->debug("[Chi2LibCudaHighDensity][removeBadVoronoiPeaks] >> Deleting Peak: Index=%i , X=%i, Y=%i, Intensity=%f", i, peaks->getHostValue(i).x, peaks->getHostValue(i).y, img->getValueHost(xx,yy));
			peaks->atHost(i).valid = false;
		}
	}
	peaks->copyToDevice();
	peaks->keepValids();

	MyLogger::log()->debug("[Chi2LibCudaHighDensity][removeBadVoronoiPeaks] Removing complete");
}

