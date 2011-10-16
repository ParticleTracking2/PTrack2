/*
 * Algorithm.h
 *
 *  Created on: 12-06-2011
 *      Author: juanin
 */

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
	None_Algorithm
};

class Algorithm {
public:
	MyMatrix<double>* data;
	Algorithm();
	virtual ~Algorithm();

	static AlgorithmType translate(string alg);
	void setData(MyMatrix<double>* data);
	virtual vector<MyPeak> run(ParameterContainer *pc);
};

#endif
