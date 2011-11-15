/*
 * Algorithm.h
 *
 *  Created on: 12-06-2011
 *      Author: juanin
 */

#include "../Image/MyImage.h"
#include "../Container/MyMatrix.h"
#include "../Container/ParameterContainer.h"
#include "../Utils/MyLogger.h"
#include "MyPeak.h"
#include <vector>

#ifndef ALGORITHM
#define ALGORITHM

using namespace std;

enum AlgorithmType{
	Chi2_Algorithm,
	Chi2HD_Algorithm,
	Chi2HDCuda_Algorithm,
	None_Algorithm
};

class Algorithm {
public:
	MyMatrix<double>* data;
	bool use_threads;
	Algorithm();
	virtual ~Algorithm();

	static AlgorithmType translate(string alg);
	void setData(MyMatrix<double>* data);
	void setThreads(bool use);
	virtual vector<MyPeak> run(ParameterContainer *pc);
};

#endif
