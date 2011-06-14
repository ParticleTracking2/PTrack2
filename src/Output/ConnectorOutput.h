/*
 * ConnectorOutput.h
 *
 *  Created on: 13-06-2011
 *      Author: juanin
 */
#include "Output.h"

#ifndef CONNECTOROUTPUT
#define CONNECTOROUTPUT

class ConnectorOutput: public Output {
public:
	ConnectorOutput();
	virtual ~ConnectorOutput();
	static string name();
	void writeData(void* data);
};

#endif
