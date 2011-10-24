/*
 * Output.h
 *
 *  Created on: 13-06-2011
 *      Author: juanin
 */
#include "../Algorithm/MyPeak.h"
#include "../Utils/MyLogger.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#ifndef OUTPUT
#define OUTPUT

enum OutputType{
	Standar_out,
	Plain_out,
	Binary_out,
	Connector_out
};

using namespace std;

class Output {
public:
	static OutputType translate(string out);
	virtual ~Output() { };
	virtual void writeData(vector<MyPeak> *peaks, string file);
};

#endif
