/*
 * PeaksStep.h
 *
 *  Created on: 12/09/2011
 *      Author: juanin
 */
#include "../AlgorithmStepHandler.h"
#include "../../Container/Array2D.h"
#include "../Objects_Chi2/MyPeak.h"
#include <vector>
#include <math.h>
#include <algorithm>
#include <time.h>

#ifndef PEAKSSTEP
#define PEAKSSTEP

class PeaksStep: public AlgorithmStepHandler {
private:
	int _threshold;
	int _minsep;
	int _mindistance;

	static bool findLocalMinimum(Array2D<double> *img, unsigned int imgX, unsigned int imgY, int minsep);
	static vector<MyPeak> validatePeaks(vector<MyPeak> *peaks, int mindistance);
public:
	PeaksStep();
	void handleData(ParameterContainer *pc);

	void setThreshold(int threshold);
	void setMinSeparation(int minsep);
	void setMinDistance(int mindistance);

	static vector<MyPeak> getPeaks(Array2D<double> *img, int threshold, int mindistance, int minsep);
};

#endif /* PEAKSSTEP */
