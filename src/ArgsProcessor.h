/*
 * ArgsProcessor.h
 *
 *  Created on: 13-06-2011
 *      Author: juanin
 */
#include <iostream>
#include <string>
using namespace std;

#ifndef ARGSPROCESSOR
#define ARGSPROCESSOR

class ArgsProcessor {
private:
	static ArgsProcessor *myInstance;
	ArgsProcessor();
	virtual ~ArgsProcessor();

public:
	static string name();
	static ArgsProcessor *getInstance();
	void setArgs(int argcount, char* argvalues[]);
};

#endif
