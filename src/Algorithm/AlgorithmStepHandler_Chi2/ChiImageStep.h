/*
 * ChiImageStep.h
 *
 *  Created on: 26/08/2011
 *      Author: juanin
 */
#include "../AlgorithmStepHandler.h"
#include "../../Container/Array2D.h"
#include "fftw3.h"

#ifndef CHIIMAGESTEP
#define CHIIMAGESTEP

class ChiImageStep: public AlgorithmStepHandler {
private:
	static Array2D<double>* conv2d_fft(Array2D<double> *img, Array2D<double> *kernel_img);
	static Array2D<double>* getFirstTerm(Array2D<double> *img, Array2D<double> *kernel_img);
	static Array2D<double>* getSecondTerm(Array2D<double> *img, Array2D<double> *kernel_img);
	static Array2D<double>* getThirdTerm(Array2D<double> *img, Array2D<double> *kernel_img);
public:
	void handleData(ParameterContainer *pc);
	static Array2D<double>* getChiImage(Array2D<double> *base_img, Array2D<double> *kernel_img);
	void printDescription();
};

#endif
