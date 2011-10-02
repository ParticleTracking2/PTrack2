/*
 * Chi2Algorithm.h
 *
 *  Created on: 12-06-2011
 *      Author: juanin
 */
#include "Algorithm.h"
#include "AlgorithmStepHandler_Chi2/NormalizeStep.h"
#include "AlgorithmStepHandler_Chi2/ChiImageStep.h"
#include "AlgorithmStepHandler_Chi2/PeaksStep.h"
#include "AlgorithmStepHandler_Chi2/ParticleGridStep.h"
#include "AlgorithmStepHandler_Chi2/ChiDifferenceStep.h"

#include "AlgorithmStepHandler_Chi2/AddMissedPeaksStep.h"
#include "AlgorithmStepHandler_Chi2/ReComputeGridAndDiff.h"
#include "AlgorithmStepHandler_Chi2/Chi2Minimization.h"

#ifndef CHI2ALGORITHM
#define CHI2ALGORITHM

class Chi2Algorithm: public Algorithm {
private:
	ParameterContainer *pc_chi;
public:
	Chi2Algorithm();
	virtual ~Chi2Algorithm();

	void run();
	void setInitialValues(ParameterContainer *pc);
};

#endif
