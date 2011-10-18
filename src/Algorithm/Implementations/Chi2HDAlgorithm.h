/*
 * Chi2Algorithm.h
 *
 *  Created on: 12-06-2011
 *      Author: juanin
 */

#include "../Algorithm.h"
#include "../Chi2Lib/Chi2Lib.h"
#include "../Chi2Lib/Chi2LibHighDensity.h"
#include "../Chi2Lib/Chi2LibMatrix.h"
#include "../Chi2Lib/Chi2LibFFTW.h"
#include "../Chi2Lib/Chi2LibFFTWCache.h"

#ifndef CHI2HDALGORITHM
#define CHI2HDALGORITHM

using namespace std;

class Chi2HDAlgorithm: public Algorithm {
public:
	vector<MyPeak> run(ParameterContainer *pc);
};

#endif
