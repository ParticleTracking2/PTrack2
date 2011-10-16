/*
 * ArgsProcessor.h
 *
 *  Created on: 13-06-2011
 *      Author: juanin
 */
#include <stdlib.h>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include "Obj/KeyTreat.h"
#include "../Output/Output.h"
#include "../Container/ParameterContainer.h"
#include "../Container/Container.h"
#include "../Utils/MyLogger.h"
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
	vector <ArgObj> vParams;
	/* Actual algoritmo seleccionado */
	AlgorithmType currentAlgorithmType;
	OutputType currentOutputType;

	/**
	 * Constructor privado, aqui se establecen los parametros aceptables para cada algoritmo
	 */
	ArgsProcessor();

	/**
	 * Retorna un arreglo de Chars en letras minusculas
	 */
	string toLowerCase(char *str);

	/**
	 * Modifica el string para tener solo letras minusculas
	 */
	void toLowerCase(string &str);

	/**
	 * Retorna el indice de aparicion de la llave dentro de los argumentos.
	 * De no encontrarse retorna un -1
	 */
	int find(string key, int argcount, char* argvalues[]);

	/**
	 * Chequea que los parametros sean correctos acoorde a los algoritmos
	 */
	void checkArgs(ArgObj *currentArgs, int argcount, char* argvalues[]);

public:
	virtual ~ArgsProcessor();

	static ArgsProcessor *getInstance();

	static void printHelp();

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

	/**
	 * Devuelve el contenedor
	 */
	ParameterContainer *getContainer();

	/**
	 * Devuelve el algoritmo seleccionado
	 */
	AlgorithmType getAlgorithmType();

	/**
	 * Devuelve el tipo de salida seleccionada
	 */
	OutputType getOutputType();
};

#endif
