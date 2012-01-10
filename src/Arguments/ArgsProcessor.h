/*
 * ArgsProcessor.h
 *
 *  Created on: 13-06-2011
 *      Author: juanin
 */
#include <stdlib.h>
#include <string>
#include <vector>
#include <algorithm>
#include "Obj/KeyTreat.h"
#include "../Algorithm/AlgorithmExecutor.h"
#include "../Output/Output.h"
#include "../Container/ParameterContainer.h"
#include "../Container/Container.h"
#include "../Utils/MyLogger.h"
using namespace std;

#ifndef ARGSPROCESSOR
#define ARGSPROCESSOR

/**
 * Clase para manejar pos argumentso de ejecucion del programa.
 * Esta clase es un Singleton por lo que solo se instancia una vez y es global en todas las llamadas a esta.
 */
class ArgsProcessor {
private:
	/**
	 * Unica instancia de la clase.
	 */
	static ArgsProcessor *myInstance;

	/**
	 * Contenedor de Parametros interpretados y aceptados.
	 */
	ParameterContainer *pc;

	/**
	 * Vector de ArgObj. Es un vector de parametros aceptables e interpretables.
	 */
	vector <ArgObj> vParams;

	/**
	 * Vector de KeyTreat. Vector de parametros aceptables generales, para todos los arlgoritmos.
	 */
	vector <KeyTreat> gParams;

	/**
	 * Algoritmo seleccionado a ejecutar segun los parametros recibidos.
	 */
	AlgorithmType currentAlgorithmType;

	/**
	 * Metodo de salida de datos seleccionado.
	 */
	OutputType currentOutputType;

	/**
	 * Parametro siguiente al de salida. Generalmente un archivo.
	 */
	string currentOutputFile;

	/**
	 * Constructor privado. Aquí se establecen los parametros aceptables para cada algoritmo
	 */
	ArgsProcessor();

	/**
	 * Retorna un arreglo de Chars en letras minusculas
	 * @param str Arreglo de char para ser convertido a minusculas.
	 * @return String con solo letras minusculas.
	 */
	string toLowerCase(char *str);

	/**
	 * Modifica el string para tener solo letras minusculas
	 * @param str String para ser convertido a minusculas.
	 */
	void toLowerCase(string &str);

	/**
	 * Retorna el indice de aparicion de la llave dentro de los argumentos.
	 * De no encontrarse retorna un -1
	 * @param key Llave a ser encontrada dentro de los argumentso
	 * @param argcount Cantidad de argumentos recibidos.
	 * @param argvalues Arreglo con los valores de los argumentos
	 * @return Indice donde se encuentra la llave dentro de los argumentos, -1 en caso de no encontrarse.
	 */
	int find(string key, int argcount, char* argvalues[]);

	/**
	 * Chequea que los argumentos ingresados sean correctos acoorde al algoritmo seleccionado.
	 * De no reconocer un argumento, se escribe un mensaje en pantalla en forma de advertencia.
	 * @param currentArgs Argumentos aceptables
	 * @param argcount Cantidad de argumentos recibidos.
	 * @param argvalues Arreglo con los valores de los argumentos
	 */
	void checkArgs(ArgObj *currentArgs, int argcount, char* argvalues[]);

public:
	/**
	 * Destructor virtual.
	 */
	virtual ~ArgsProcessor();

	/**
	 * Obtiene la única instancia de la clase, si esta no existe se crea.
	 * @return Puntero a la instancia de la clase.
	 */
	static ArgsProcessor *getInstance();

	/**
	 * Imprime en pantalla la explicacion y el uso de cada algoritmo y sus argumentos.
	 */
	static void printHelp();

	/**
	 * Imprime en pantalla la explicacion y el uso de cada algoritmo y sus argumentos.
	 */
	static void printHelp(ArgObj currentArgs);

	/**
	 * Imprime en pantalla la explicacion y el uso de cada algoritmo y sus argumentos.
	 */
	static void printGeneralHelp();

	/**
	 * Establece, almacena e interpreta los argumentos de ejecucion a partir de los argumentos ingresados
	 * al momento de ejecutar el programa.
	 * @param argcount Cantidad de argumentos recibidos.
	 * @param argvalues Arreglo con los valores de los argumentos
	 */
	void setArgs(int argcount, char* argvalues[]);

	/**
	 * Obtiene todas las llaves validas ingresadas como argumentos.
	 * @return Vector de strings con todas las llaves validas ingresadas como argumentos.
	 */
	vector <string> getKeys();

	/**
	 * Verifica que una llave exista dentro de los argumentos validamente ingresados.
	 * @param key Llave a ser buscada.
	 * @return True si se encuentra la llave, false en caso contrario.
	 */
	bool hasKey(string key);

	/**
	 * Obtiene el valor de un argumento valido en forma de entero.
	 * @param key Llave del argumento
	 * @return valor como entero
	 */
	int getArgAsInt(string key);

	/**
	 * Obtiene el valor de un argumento valido en forma de double.
	 * @param key Llave del argumento
	 * @return valor como Double
	 */
	double getArgAsDouble(string key);

	/**
	 * Obtiene el valor de un argumento valido en forma de String.
	 * @param key Llave del argumento
	 * @return valor como String
	 */
	string getArgAsString(string key);

	/**
	 * Devuelve el contenedor de parametros.
	 * @return Contenedor de parametros
	 */
	ParameterContainer *getContainer();

	/**
	 * Devuelve el algoritmo seleccionado segun los argumentos ingresados.
	 * @return Tipo de algoritmo a ejecutar.
	 */
	AlgorithmType getAlgorithmType();

	/**
	 * Devuelve el tipo de salida de datos seleccionada segun los argumentos ingresados.
	 * @return Tipo de salida de datos.
	 */
	OutputType getOutputType();

	/**
	 * Devuelve el string siguiente al tipo de salida, que generalemte es un archivo.
	 * @return string con parametro de salida
	 */
	string getOutputString();
};

#endif
