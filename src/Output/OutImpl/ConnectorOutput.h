/*
 * ConnectorOutput.h
 *
 *  Created on: 13-06-2011
 *      Author: juanin
 */
#include "../Output.h"

#ifndef CONNECTOROUTPUT
#define CONNECTOROUTPUT

/**
 * Implementacion teorica de Output para una salida de red.
 */
class ConnectorOutput: public Output {
public:

	/**
	 * Escribe los datos de peaks a una conexion de datos, como un socket.
	 * @param peaks Vector de datos MyPeak a ser representados
	 * @param file Parametro irrelevante
	 */
	void writeData(vector<MyPeak> *peaks, string file);
};

#endif
