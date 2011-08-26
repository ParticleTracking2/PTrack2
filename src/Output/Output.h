/*
 * Output.h
 *
 *  Created on: 13-06-2011
 *      Author: juanin
 */
#include <iostream>
using namespace std;

#ifndef OUTPUT
#define OUTPUT

class Output {
public:
	virtual ~Output() { };
	virtual void writeData(void* data);
};

#endif
