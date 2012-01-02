/*
 * KeyTreat.h
 *
 *  Created on: 11/10/2011
 *      Author: juanin
 */

#include "../../Algorithm/Algorithm.h"
#include <vector>
#include <string>

#ifndef KEYTREAT
#define KEYTREAT

using namespace std;

/**
 * Tipo de tratamiento de argumentos.
 */
enum TreatType{
	Require_Treat,			/**< Tipo de argumento requerido para la ejecucion. */
	Followed_String_Treat,	/**< Tipo de argumento seguido por un string. */
	Followed_Int_Treat,		/**< Tipo de argumento seguido por un entero. */
	Followed_Double_Treat,	/**< Tipo de argumento seguido por un double. */
	Exist_Treat,			/**< Tipo de argumento que requiere solo su existencia. */
	Output_Treat			/**< Tipo de argumento para salida de datos. */
};

/**
 * Estructura para describir un argumento.
 * El argumento debe tener una llave, una descripcion, un ejemplo de uso y una
 * serie de tratamientos para ser procesado.
 */
struct KeyTreat{
	/**
	 * Llave del argumento.
	 */
	string key;

	/**
	 * Descripcion.
	 */
	string description;

	/**
	 * Ejemplo de su uso.
	 */
	string example;

	/**
	 * Lista de tratamientos de los datos para poder ser correctamente interpretado.
	 */
	vector<TreatType> treat;
};

/**
 * Estructura para poder procesar correctamente los argumentos necesarios para ejecutar un algoritmo.
 * Este debe contener un tipo de algoritmo, una llave, una descripcion, un ejemplo de uso y una serie de argumentos
 * aceptables.
 */
struct ArgObj{
	/**
	 * Tipo de algoritmo.
	 */
	AlgorithmType type;

	/**
	 * Llave representativa del algoritmo.
	 */
	string argkey;

	/**
	 * Descripcion del algoritmo.
	 */
	string description;

	/**
	 * Ejemplo de uso.
	 */
	string example;

	/**
	 * Serie de argumentos aceptables por el algoritmo.
	 */
	vector<KeyTreat> keys_treats;
};

#endif
