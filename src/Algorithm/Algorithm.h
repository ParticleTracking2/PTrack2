/*
 * Algorithm.h
 *
 *  Created on: 12-06-2011
 *      Author: juanin
 */
#include "AlgorithmStepHandler/AlgorithmStepHandler.h"
#include "AlgorithmStepHandler/Chi2Step.h"
#include "AlgorithmStepHandler/ChiDifferenceStep.h"
#include "AlgorithmStepHandler/ChiImagePeaksStep.h"
#include "AlgorithmStepHandler/CUFFTStep.h"
#include "AlgorithmStepHandler/FFTWStep.h"
#include "AlgorithmStepHandler/NewtonParticleCenterStep.h"
#include "AlgorithmStepHandler/NewtonParticleDWStep.h"
#include "AlgorithmStepHandler/NormalizeStep.h"
#include "AlgorithmStepHandler/ParticleGridStep.h"
#include "../Container/ParameterContainer.h"
#include "../Container/Container.h"

#include <iostream>
#include <string>
using namespace std;

#ifndef ALGORITHM
#define ALGORITHM

class Algorithm {
public:
	static string name();
	virtual void run();
	virtual void setInitialValues(ParameterContainer *pc);
};

#endif
