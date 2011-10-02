/*
 * Chi2Minimization.h
 *
 *  Created on: 01/10/2011
 *      Author: juanin
 */

#include "../AlgorithmStepHandler.h"
#include "../Objects_Chi2/MyPeak.h"
#include "ParticleGridStep.h"
#include "ChiDifferenceStep.h"

#ifndef CHI2MINIMIZATION
#define CHI2MINIMIZATION

class Chi2Minimization: public AlgorithmStepHandler {
private:
	int _minChi2Delta;
	unsigned int _maxIterations;
public:
	Chi2Minimization();
	void handleData(ParameterContainer *pc);
	static pair< vector<double>, vector<double> > newtonCenter(Array2D<int> *over, vector<double> *px, vector<double> *py, Array2D<double> *diff, vector<MyPeak> *peaks, int shift, double D, double w, double dp, double maxdr = 20.0);
	void printDescription();

	unsigned int getMaxIterations();
	int getMinChi2Delta();

	void setMaxIterations(unsigned int iterations);
	void setMinChi2Delta(int delta);
};

#endif
