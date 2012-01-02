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

/**
 * Clase Factory para crear objetos de salida de datos.
 */
class OutputFactory {
public:

	/**
	 * Genera un objeto de salida de datos segun el tipo entregado.
	 * @param otype Tipo de objeto a crear.
	 * @return Objeto de salida de datos heredado de la clase Output
	 */
	static Output *makeOutputGenerator(OutputType otype);
};

#endif
