/*
 * Algorithm.h
 *
 *  Created on: 12-06-2011
 *      Author: juanin
 */

#include "../Arguments/Obj/KeyTreat.h"
#include "../Image/MyImage.h"
#include "../Image/MyImageFactory.h"
#include "../Container/MyMatrix.h"
#include "../Container/ParameterContainer.h"
#include "../Utils/MyLogger.h"
#include "MyPeak.h"
#include <vector>

#ifndef ALGORITHM
#define ALGORITHM

using namespace std;

/**
 * Clase base para implementar algoritmos en base a Imagenes usando estructura MyMatrix<double>*.
 * Puede modificarse a futuro. Se debe implementar al menos la funcion "vector<MyPeak> run(ParameterContainer *pc);"
 */
class Algorithm {
public:
	/**
	 * Constructor vacio.
	 */
	Algorithm();

	/**
	 * Indica el uso o no de threads dentro del procesamiento.
	 */
	bool use_threads;

	/**
	 * Destructor
	 */
	virtual ~Algorithm();

	/**
	 * Devuelve los parametros que acepta este Algoritmo.
	 * @return Todos los parametros que acepta este algoritmo para ejecutar.
	 */
	static ArgObj myArgs();

	/**
	 * Establece los datos para ser procesados.
	 * @param pc Parametros que ocupa el algoritmo para correr.
	 */
	virtual void setData(ParameterContainer *pc);

	/**
	 * Principal funcion a implementar. Se ingresa un puntero a un objeto ParameterContainer con los parametros
	 * necesarios para la ejecucion optima del algoritmo.
	 * @return Vector de MyPeak representando los peaks encontrados dentro de los datos entregados.
	 */
	virtual vector<MyPeak> run();
};

#endif
