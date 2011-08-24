/*
 * ArgsProcessor.h
 *
 *  Created on: 13-06-2011
 *      Author: juanin
 */
#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <vector>
#include "Container/ParameterContainer.h"
#include "Container/Container.h"
using namespace std;

#ifndef ARGSPROCESSOR
#define ARGSPROCESSOR

class ArgsProcessor {
private:
	/* Unica instancia accesible de la calse. */
	static ArgsProcessor *myInstance;
	/* Contenedor de los parametros. */
	ParameterContainer *pc;
	/* Paramatros aceptables */
	vector <string> vParams;
	ArgsProcessor();
	virtual ~ArgsProcessor();

public:
	static string name();
	static ArgsProcessor *getInstance();

	/**
	 * Establece y almacena los argumentos de ejecucion a partir
	 * de los argumentos ingresados al momento de ejecutar el programa.
	 */
	void setArgs(int argcount, char* argvalues[]);
	/**
	 * Obtiene todas las llaves validas ingresadas como argumentos
	 */
	vector <string> getKeys();
	/**
	 * Verifica que una llave exista dentro de los argumentos
	 */
	bool hasKey(string key);
	/**
	 * Obtiene un argumento valido como entero
	 */
	int getArgAsInt(string key);
	/**
	 * Obtiene un argumento valido como double
	 */
	double getArgAsDouble(string key);
	/**
	 * Obtiene un argumento valido como string
	 */
	string getArgAsString(string key);
};

#endif
