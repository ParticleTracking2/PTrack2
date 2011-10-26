/*
 * OutputFactory.cpp
 *
 *  Created on: 13/10/2011
 *      Author: ptrack
 */

#include "OutputFactory.h"

Output *OutputFactory::makeOutputGenerator(OutputType otype){
	switch (otype) {
		case Standar_out:
			MyLogger::log()->debug("[OutputFactory] Standar Output selected");
			return new StandarOutput();
			break;
		case Plain_out:
			MyLogger::log()->debug("[OutputFactory] Plain file Output selected");
			return new PlainOutput();
			break;
		case Binary_out:
			MyLogger::log()->debug("[OutputFactory] Binary file Output selected");
			return new BinaryOutput();
			break;
		case Connector_out:
			MyLogger::log()->debug("[OutputFactory] Connector Output selected");
			return new ConnectorOutput();
			break;
	}
	return new StandarOutput();
}
