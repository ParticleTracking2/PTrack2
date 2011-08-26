/*
 * ChiImageStep.h
 *
 *  Created on: 26/08/2011
 *      Author: juanin
 */
#include "../AlgorithmStepHandler.h"
#include "fftw3.h"

#ifndef CHIIMAGESTEP
#define CHIIMAGESTEP

class ChiImageStep: public AlgorithmStepHandler {
private:
	void conv2d_fft(MyImage *img, MyImage *ipf);
public:
	ChiImageStep();
	virtual ~ChiImageStep();

	void handleData(ParameterContainer *pc);
};

#endif
