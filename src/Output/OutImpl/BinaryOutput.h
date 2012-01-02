/*
 * BinaryOutput.h
 *
 *  Created on: 13-06-2011
 *      Author: juanin
 */
#include "../Output.h"

#ifndef BINARYOUTPUT
#define BINARYOUTPUT

/**
 * Implmentacion de Output para un archivo en formato binario.
 */
class BinaryOutput: public Output {
public:

	/**
	 * Escribe en un archivo binario los datos de peaks, todos como float32.
	 * @param peaks Vector de datos MyPeak a ser representados
	 * @param file Nombre del archivo de salida
	 */
	void writeData(vector<MyPeak> *peaks, string file);
};

#endif
