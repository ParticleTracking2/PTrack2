/*
 * Output.h
 *	Clase para implementar una salida de datos del programa.
 *	El unico metodo importante a implementar es "virtual void writeData(vector<MyPeak> *peaks, string file);"
 *  Created on: 13-06-2011
 *      Author: juanin
 */
#include "../Algorithm/MyPeak.h"
#include "../Utils/MyLogger.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#ifndef OUTPUT
#define OUTPUT

/**
 * Tipos de salida de datos implementados
 */
enum OutputType{
	Standar_out,
	Plain_out,
	Binary_out,
	Connector_out
};

using namespace std;

class Output {
public:
	/**
	 * Traductor de un String a un tipo de salida de datos.
	 */
	static OutputType translate(string out);

	/**
	 * Constructor vacio
	 */
	virtual ~Output() { };

	/**
	 * Metodo que se ingresa un vector de MyPeaks y un String dando como resultado un archivo de nombre del string
	 * cuyo contenido se representa el vector.
	 */
	virtual void writeData(vector<MyPeak> *peaks, string file);
};

#endif
