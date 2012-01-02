/*
 * Output.h
 *
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

/**
 * Clase para implementar una salida de datos del programa.
 * El único metodo importante a implementar es "virtual void writeData(vector<MyPeak> *peaks, string file);"
 */
class Output {
public:
	/**
	 * Traductor de un String a un tipo de salida de datos.
	 * @param out Tipo de salida de datos como un string
	 * @return Tipo de salida de datos
	 */
	static OutputType translate(string out);

	/**
	 * Destructor vacio.
	 */
	virtual ~Output() { };

	/**
	 * Metodo que se ingresa un vector de MyPeaks y un String dando como resultado un archivo de nombre del string
	 * cuyo contenido se representa el vector.
	 * @param peaks Vector de datos MyPeak a ser representados
	 * @param file Nombre del archivo de salida
	 */
	virtual void writeData(vector<MyPeak> *peaks, string file);
};

#endif
