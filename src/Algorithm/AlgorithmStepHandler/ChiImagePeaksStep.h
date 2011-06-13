/*
 * ChiImagePeaksStep.h
 *
 *  Created on: 12-06-2011
 *      Author: juanin
 */
#include "AlgorithmStepHandler.h"

#ifndef CHIIMAGEPEAKSSTEP
#define CHIIMAGEPEAKSSTEP

class ChiImagePeaksStep: public AlgorithmStepHandler {
public:
	ChiImagePeaksStep();
	virtual ~ChiImagePeaksStep();

	static string name();
	void handleData();
};

#endif
