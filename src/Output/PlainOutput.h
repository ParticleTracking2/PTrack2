/*
 * PlainOutput.h
 *
 *  Created on: 13-06-2011
 *      Author: juanin
 */
#include "Output.h"

#ifndef PLAINOUTPUT
#define PLAINOUTPUT

class PlainOutput : public Output{
public:
	PlainOutput();
	virtual ~PlainOutput();
	static string name();
	void writeData(void* data);
};

#endif
