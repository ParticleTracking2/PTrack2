/*
 * Output.h
 *
 *  Created on: 13-06-2011
 *      Author: juanin
 */
#include <iostream>
#include <string>
using namespace std;

#ifndef OUTPUT
#define OUTPUT

class Output {
public:
	static string name();
	virtual void writeData(void* data);
};

#endif
