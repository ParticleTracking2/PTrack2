/*
 * PlainOutput.h
 *
 *  Created on: 13-06-2011
 *      Author: juanin
 */
#include "../Output.h"

#ifndef PLAINOUTPUT
#define PLAINOUTPUT

/**
 * Implementacion de Output para un archivo de texto plano.
 */
class PlainOutput : public Output{
public:

	/**
	 * Escribe en un archivo en texto plano los datos de peaks.
	 * @param peaks Vector de datos MyPeak a ser representados
	 * @param file Nombre del archivo de salida
	 */
	void writeData(vector<MyPeak> *peaks, string file);
};

#endif
