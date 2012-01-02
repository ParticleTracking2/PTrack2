/*
 * Algorithm.h
 *
 *  Created on: 12-06-2011
 *      Author: juanin
 */

#include "../Image/MyImage.h"
#include "../Container/MyMatrix.h"
#include "../Container/ParameterContainer.h"
#include "../Utils/MyLogger.h"
#include "MyPeak.h"
#include <vector>

#ifndef ALGORITHM
#define ALGORITHM

using namespace std;

/**
 * Tipos de algoritmos implementados actualmente
 */
enum AlgorithmType{
	Chi2_Algorithm,
	Chi2HD_Algorithm,
	Chi2HDCuda_Algorithm,
	None_Algorithm
};

/**
 * Clase base para implementar algoritmos en base a Imagenes usando estructura MyMatrix<double>*.
 * Puede modificarse a futuro. Se debe implementar al menos la funcion "vector<MyPeak> run(ParameterContainer *pc);"
 */
class Algorithm {
public:
	/**
	 * Datos de entrada.
	 */
	MyMatrix<double>* data;

	/**
	 * Indicador de uso o no uso de threads en CPU
	 */
	bool use_threads;

	/**
	 * Constructor.
	 */
	Algorithm();

	/**
	 * Destructor
	 */
	virtual ~Algorithm();

	/**
	 * Obtiene un string representativo de un tipo de algoritmo y devuelve ese tipo.
	 * @param alg String representando un tipo de algoritmo.
	 * @return Tipo de algoritmo.
	 */
	static AlgorithmType translate(string alg);

	/**
	 * Establece los datos para ser procesados.
	 * @param data Datos a ser procesados en forma de Matriz.
	 */
	void setData(MyMatrix<double>* data);

	/**
	 * Establece el uso de threads en CPU.
	 * @param use Uso de Threads (True) o ejecucion lineal (False).
	 */
	void setThreads(bool use);

	/**
	 * Principal funcion a implementar. Se ingresa un puntero a un objeto ParameterContainer con los parametros
	 * necesarios para la ejecucion optima del algoritmo.
	 * @param pc Parametros que ocupa el algoritmo para correr.
	 * @return Vector de MyPeak representando los peaks encontrados dentro de los datos entregados.
	 */
	virtual vector<MyPeak> run(ParameterContainer *pc);
};

#endif
