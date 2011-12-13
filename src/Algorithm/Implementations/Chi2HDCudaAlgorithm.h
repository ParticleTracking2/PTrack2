/*
 * Chi2HDCudaAlgorithm.h
 *
 *  Created on: 15-11-2011
 *      Author: ptrack
 */

#ifndef CHI2HDCUDAALGORITHM
#define CHI2HDCUDAALGORITHM

#include "../Algorithm.h"
#include "../../Utils/FileUtils.h"
#include "../Chi2Lib/Chi2Lib.h"
#include "../Chi2LibCuda/Chi2LibCuda.h"
#include "../Chi2LibCuda/Chi2LibCudaFFT.h"
#include "../Chi2LibCuda/Chi2LibCudaFFTCache.h"
#include "../Chi2LibCuda/Chi2LibCudaHighDensity.h"
#include "Container/cuMyMatrix.h"
#include "Container/cuMyPeak.h"

using namespace std;

class Chi2HDCudaAlgorithm: public Algorithm {
public:
	vector<MyPeak> run(ParameterContainer *pc);
};

#endif
