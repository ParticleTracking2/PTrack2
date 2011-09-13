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
};

#endif /* PARTICLEGRIDSTEP */
