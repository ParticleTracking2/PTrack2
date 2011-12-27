/*
 * OutputFactory.h
 *	Clase Factory para crear objetos de escritura de salida para el programa.
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
	/**
	 * Genera un objeto de escritura de salida de datos segun el tipo entregado.
	 */
	static Output *makeOutputGenerator(OutputType otype);
};

#endif
