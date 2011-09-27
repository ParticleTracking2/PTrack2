/*
 * ChiDifferenceStep.h
 *
 *  Created on: 26/09/2011
 *      Author: ptrack
 */
#include "../AlgorithmStepHandler.h"
#include "math.h"

#ifndef CHIDIFFERENCESTEP
#define CHIDIFFERENCESTEP

class ChiDifferenceStep: public AlgorithmStepHandler {
public:
	void handleData(ParameterContainer *pc);
	static Array2D<double>* computeDifference(Array2D<double> *img, Array2D<double> *grid_x, Array2D<double> *grid_y, double d, double w);
};

#endif /* CHIDIFFERENCESTEP */
