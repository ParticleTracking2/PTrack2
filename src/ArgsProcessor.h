/*
 * ArgsProcessor.h
 *
 *  Created on: 13-06-2011
 *      Author: juanin
 */
#include <iostream>
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
};

#endif
