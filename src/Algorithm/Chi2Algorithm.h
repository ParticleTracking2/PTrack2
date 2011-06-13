/*
 * Chi2Algorithm.h
 *
 *  Created on: 12-06-2011
 *      Author: juanin
 */
#include "Algorithm.h"

#ifndef CHI2ALGORITHM
#define CHI2ALGORITHM

class Chi2Algorithm: public Algorithm {
public:
	static string name();
	Chi2Algorithm();
	virtual ~Chi2Algorithm();
	void run();
};

#endif
