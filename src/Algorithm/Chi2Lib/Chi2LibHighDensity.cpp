/*
 * Chi2LibHighDensity.cpp
 *
 *  Created on: 03/10/2011
 *      Author: ptrack
 */

#include "Chi2LibHighDensity.h"

void Chi2LibHighDensity::generateScaledImage(MyMatrix<double> *diff, MyMatrix<double> *out){
	MyLogger::log()->debug("[Chi2LibHighDensity][generateScaledImage] Scaling ");
	//scalematrix
	for(unsigned int x=0; x < diff->sX(); ++x){
		for(unsigned int y=0; y < diff->sY(); ++y){
			out->at(x,y) = 4*diff->getValue(x,y)*diff->getValue(x,y);
		}
	}

	MyLogger::log()->debug("[Chi2LibHighDensity][generateScaledImage] Finding Maximum and Minimum ");
	//find maxima
	pair<double,double> maxMin = Chi2Lib::getHighLow(out);
	double maxval = maxMin.first;

	MyLogger::log()->debug("[Chi2LibHighDensity][generateScaledImage] Inverting ");
	//inverse data
	for(unsigned int x=0; x < diff->sX(); ++x)
		for(unsigned int y=0; y < diff->sY(); ++y){
			out->at(x,y) = maxval - out->getValue(x,y);
		}

	MyLogger::log()->debug("[Chi2LibHighDensity][generateScaledImage] Normalizing ");
	//normalize data
	Chi2Lib::normalizeImage(out, maxMin.first, maxMin.second);
}

unsigned int Chi2LibHighDensity::checkInsidePeaks(vector<MyPeak> *old_peaks, vector<MyPeak> *new_peaks, MyMatrix<double> *img, unsigned int os){
	unsigned int totalinside = 0;
	MyLogger::log()->debug("[Chi2LibHighDensity][checkInsidePeaks] Checking inside peaks ");
	//check if NEW points are inside the image (clean newpeaks)
	MyPeak tmppk;
	for(unsigned int i=0; i < new_peaks->size(); ++i){
		tmppk = new_peaks->at(i);
		if(	0 <= (tmppk.x - os) && (tmppk.x - os) < img->sX() &&
			0 <= (tmppk.y - os) && (tmppk.y - os) < img->sY()){
			new_peaks->at(i).px = 1.0*new_peaks->at(i).x;
			new_peaks->at(i).py = 1.0*new_peaks->at(i).y;
			old_peaks->push_back(new_peaks->at(i));
			totalinside++;
		}
	}
	MyLogger::log()->debug("[Chi2LibHighDensity][checkInsidePeaks] Total peaks inside image %i of %i ",new_peaks->size(), totalinside);
	new_peaks->clear();
	return totalinside;
}

void Chi2LibHighDensity::filterPeaksOutside(vector<MyPeak> *peaks, MyMatrix<double> *img, unsigned int ss){
	MyLogger::log()->debug("[Chi2Algorithm][filterPeaksOutside] Filtering peaks outside image");
	for(unsigned int i=0; i < peaks->size(); ++i){
		if( 0 <= peaks->at(i).x - ss && peaks->at(i).x - ss < img->sX() &&
			0 <= peaks->at(i).y - ss && peaks->at(i).y - ss < img->sY()){
			// Esta adentro, no se hace nada.
		}else{
			peaks->erase(peaks->begin()+i);
			--i;
		}
	}
	MyLogger::log()->debug("[Chi2Algorithm][filterPeaksOutside] Filtering complete");
}

pair<double,double> Chi2LibHighDensity::gaussianFit(vector<MyPeak> *peaks, MyMatrix<double> *img, unsigned int ss){
	unsigned int slots = 21;

	MyLogger::log()->debug("[Chi2LibHighDensity][gassianFit] Calculating MU and SIGMA ");
	vector<double> X(slots);
	vector<int> freq(slots);
	double dx = 0.01;
	for(unsigned int i=0; i < slots; ++i){
		freq[i]=0;
		X[i]=0.8+i*dx;
	}

	vector<MyPeak> new_peaks;
	new_peaks.reserve(peaks->size());
	MyPeak tmp;
	for(unsigned int i=0; i < peaks->size(); ++i){
			tmp.x = peaks->at(i).x - ss;
			tmp.y = peaks->at(i).y - ss;
			tmp.intensity = img->getValue(tmp.x, tmp.y);
			new_peaks.push_back(tmp);
	}

	sort(new_peaks.begin(), new_peaks.end(), MyPeak::compareMe);

	unsigned int current = 0;
	for(unsigned int i=0; i < new_peaks.size(); ++i){
		for(unsigned int s=current; s < slots; ++s){
			if(new_peaks.at(i).intensity <= X[s] + dx){
				++freq[s];
				break;
			}
			++current;
		}
	}

	int check = 0;
	double mu = 0.0, sigma = 0.0;
	for(unsigned int i=0; i < slots; ++i){
		mu += X[i]*freq[i];
		check += freq[i];
	}
	mu = mu/check;

	for(unsigned int i=0; i < slots; ++i){
		sigma += freq[i]*(mu-X[i])*(mu-X[i]);
	}
	sigma = sqrt(sigma/check);

	MyLogger::log()->debug("[Chi2LibHighDensity][gassianFit] Total Checks=%i; Returning MU=%f; SIGMA=%f", check, mu, sigma);
	pair<double, double> ret; ret.first = mu; ret.second = sigma;
	return ret;
}

void Chi2LibHighDensity::removeBadPeaks(vector<MyPeak> *peaks, MyMatrix<double> *img, double vor_threshold, double par_threshold, unsigned int ss){
	MyLogger::log()->debug("[Chi2LibHighDensity][removeBadPeaks] Starting removing peaks by Area < %f and Intensity < %f", vor_threshold, par_threshold);
	Chi2LibQhull::addVoronoiAreas(peaks);

	int xx = 0, yy = 0;
	for(unsigned int i=0; i < peaks->size(); ++i){
		xx = peaks->at(i).x - ss;
		yy = peaks->at(i).y - ss;
		if(img->getValue(xx,yy) < par_threshold && peaks->at(i).vor_area < vor_threshold){
			// Remove Peak element at this position
			MyLogger::log()->debug("[Chi2LibHighDensity][removeBadPeaks] >> Deleting Peak: Index=%i , X=%i, Y=%i, Intensity=%f, VoronoiArea=%f", i, peaks->at(i).x, peaks->at(i).y, img->getValue(xx,yy), peaks->at(i).vor_area );
			peaks->erase(peaks->begin()+i);
			--i;
		}
	}
	MyLogger::log()->debug("[Chi2LibHighDensity][removeBadPeaks] Removing complete");
}

void Chi2LibHighDensity::removeBadIntensityPeaks(vector<MyPeak> *peaks, MyMatrix<double> *img, double par_threshold, unsigned int ss){
	MyLogger::log()->debug("[Chi2LibHighDensity][removeBadPeaks] Starting removing peaks by Intensity of image < %f", par_threshold);

	int xx = 0, yy = 0;
	for(unsigned int i=0; i < peaks->size(); ++i){
		xx = peaks->at(i).x - ss;
		yy = peaks->at(i).y - ss;
		if(img->getValue(xx,yy) < par_threshold ){
			// Remove Peak element at this position
			MyLogger::log()->debug("[Chi2LibHighDensity][removeBadPeaks] >> Deleting Peak: Index=%i , X=%i, Y=%i, Intensity=%f, VoronoiArea=%f", i, peaks->at(i).x, peaks->at(i).y, img->getValue(xx,yy), peaks->at(i).vor_area );
			peaks->erase(peaks->begin()+i);
			--i;
		}
	}
	MyLogger::log()->debug("[Chi2LibHighDensity][removeBadPeaks] Removing complete");
}

void Chi2LibHighDensity::removeBadVoronoiPeaks(vector<MyPeak> *peaks, MyMatrix<double> *img, double vor_threshold, unsigned int ss){
	MyLogger::log()->debug("[Chi2LibHighDensity][removeBadPeaks] Starting removing peaks by Voronoi Area < %f", vor_threshold);

	for(unsigned int i=0; i < peaks->size(); ++i){
		if(0 < peaks->at(i).vor_area && peaks->at(i).vor_area < vor_threshold ){
			// Remove Peak element at this position
			MyLogger::log()->debug("[Chi2LibHighDensity][removeBadPeaks] >> Deleting Peak: Index=%i , X=%i, Y=%i, VoronoiArea=%f", i, peaks->at(i).x, peaks->at(i).y, peaks->at(i).vor_area );
			peaks->erase(peaks->begin()+i);
			--i;
		}
	}
	MyLogger::log()->debug("[Chi2LibHighDensity][removeBadPeaks] Removing complete");
}
