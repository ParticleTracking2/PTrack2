/*
 * OutputFactory.h
 *
 *  Created on: 13/10/2011
 *      Author: ptrack
 */
#include "Output.h"
#include "OutImpl/StandarOutput.h"
#include "OutImpl/PlainOutput.h"
#include "OutImpl/BinaryOutput.h"
#include "OutImpl/ConnectorOutput.h"

#ifndef OUTPUTFACTORY
#define OUTPUTFACTORY

class OutputFactory {
public:
	static Output *makeOutputGenerator(OutputType otype);
};

#endif
