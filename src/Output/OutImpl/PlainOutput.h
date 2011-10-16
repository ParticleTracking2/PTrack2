/*
 * PlainOutput.h
 *
 *  Created on: 13-06-2011
 *      Author: juanin
 */
#include "../Output.h"

#ifndef PLAINOUTPUT
#define PLAINOUTPUT

class PlainOutput : public Output{
public:
	void writeData(vector<MyPeak> *peaks, string file = "plain_out.txt");
};

#endif
