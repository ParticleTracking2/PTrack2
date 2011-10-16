/*
 * StandarOutput.h
 *
 *  Created on: 13/10/2011
 *      Author: ptrack
 */
#include "../Output.h"

#ifndef STANDAROUTPUT
#define STANDAROUTPUT

class StandarOutput : public Output {
public:
	void writeData(vector<MyPeak> *peaks, string file = "none");
};

#endif
