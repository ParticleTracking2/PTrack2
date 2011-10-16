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

#ifndef CHI2ALGORITHM
#define CHI2ALGORITHM

using namespace std;

class Chi2Algorithm: public Algorithm {
public:
	vector<MyPeak> run(ParameterContainer *pc);
};

#endif
