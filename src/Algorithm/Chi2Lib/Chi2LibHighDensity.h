/*
 * Chi2LibHighDensity.h
 *
 *  Created on: 03/10/2011
 *      Author: ptrack
 */

#include <vector>
#include "Chi2Lib.h"
#include "Chi2LibQhull.h"
#include "../MyPeak.h"
#include "../../Utils/MyLogger.h"
#include "../../Container/MyMatrix.h"

#ifndef CHI2LIBHIGHDENSITY
#define CHI2LIBHIGHDENSITY

class Chi2LibHighDensity {
public:
	static void generateScaledImage(MyMatrix<double> *diff, MyMatrix<double> *out);

	static unsigned int checkInsidePeaks(vector<MyPeak> *old_peaks, vector<MyPeak> *new_peaks, MyMatrix<double> *img, unsigned int os);

	/**
	 * Elimina los peaks que se encuentran fuera de la imagen (Recuerdo: los peaks encontrados pueden estar fuera de la imagen original)
	 */
	static void filterPeaksOutside(vector<MyPeak> *peaks, MyMatrix<double> *img, unsigned int ss);

	static pair<double,double> gaussianFit(vector<MyPeak> *peaks, MyMatrix<double> *img, unsigned int ss);

	static void removeBadPeaks(vector<MyPeak> *peaks, MyMatrix<double> *img, double vor_threshold, double par_threshold, unsigned int ss);

	static void removeBadIntensityPeaks(vector<MyPeak> *peaks, MyMatrix<double> *img, double par_threshold, unsigned int ss);

	static void removeBadVoronoiPeaks(vector<MyPeak> *peaks, MyMatrix<double> *img, double vor_threshold, unsigned int ss);
};

#endif
