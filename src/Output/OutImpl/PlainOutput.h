/*
 * PlainOutput.h
 *	Implementacion de Output para un archivo de texto plano.
 *  Created on: 13-06-2011
 *      Author: juanin
 */
#include "../Output.h"

#ifndef PLAINOUTPUT
#define PLAINOUTPUT

class PlainOutput : public Output{
public:
	void writeData(vector<MyPeak> *peaks, string file);
};

#endif
