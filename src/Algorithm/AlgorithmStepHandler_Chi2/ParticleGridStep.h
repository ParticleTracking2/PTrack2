/*
 * ParticleGridStep.h
 *
 *  Created on: 12/09/2011
 *      Author: juanin
 */
#include "../AlgorithmStepHandler.h"
#include "../../Container/Array2D.h"
#include "../Objects_Chi2/MyPeak.h"
#include <vector>
#include <math.h>

#ifndef PARTICLEGRIDSTEP
#define PARTICLEGRIDSTEP

class ParticleGridStep: public AlgorithmStepHandler {
public:
	void handleData(ParameterContainer *pc);
	static unsigned int generateGrid(vector<MyPeak> *peaks, unsigned int ss, Array2D<double> *img, Array2D<double> *grid_x, Array2D<double> *grid_y, Array2D<int> *over);
};

#endif /* PARTICLEGRIDSTEP */
