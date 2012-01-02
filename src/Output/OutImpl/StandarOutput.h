/*
 * StandarOutput.h
 *
 *  Created on: 13/10/2011
 *      Author: ptrack
 */
#include "../Output.h"

#ifndef STANDAROUTPUT
#define STANDAROUTPUT

/**
 * Implmementacion de Output para salida estandar.
 */
class StandarOutput : public Output {
public:

	/**
	 * Escribe en la salida estandar los datos de peaks
	 * @param peaks Vector de datos MyPeak a ser representados
	 * @param file Parametro irrelevante
	 */
	void writeData(vector<MyPeak> *peaks, string file);
};

#endif
