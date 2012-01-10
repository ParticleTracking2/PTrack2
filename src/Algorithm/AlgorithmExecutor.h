/*
 * AlgorithmFactory.h
 *
 *  Created on: 11/10/2011
 *      Author: juanin
 */
#include <string>
#include <vector>
#include "../Utils/MyLogger.h"
#include "Algorithm.h"
#include "AlgorithmTypes.h"
#include "MyPeak.h"
#include "Implementations/Chi2Algorithm.h"
#include "Implementations/Chi2HDAlgorithm.h"

#ifdef CHI2CUDA
#include "Implementations/Chi2HDCudaAlgorithm.h"
#endif

#ifndef ALGORITHMEXECUTOR
#define ALGORITHMEXECUTOR

using namespace std;

/**
 * Clase Factory para construir algoritmos segun su tipo.
 */
class AlgorithmExecutor {
private:
	Algorithm *selected;
public:
	/**
	 * Crea el ejecutor de algoritmos.
	 */
	AlgorithmExecutor();

	/**
	 * Crea el ejecutor de algoritmos con un tipo seleccionado.
	 * @param type Tipo de algoritmo seleccionado.
	 */
	AlgorithmExecutor(AlgorithmType type);

	/**
	 * Destructor.
	 */
	~AlgorithmExecutor();

	/**
	 * Retorna un vector con todos los argumentos que aceptan todos los algoritmos que puede construir y ejecutar.
	 * @return Vector con argumentos de algoritmos.
	 */
	static vector<ArgObj> getAllArguments();

	/**
	 * Obtiene un string representativo de un tipo de algoritmo y devuelve ese tipo.
	 * @param alg String representando un tipo de algoritmo.
	 * @return Tipo de algoritmo.
	 */
	static AlgorithmType translate(string alg);

	/**
	 * Construye un algoritmo segun el tipo entregado.
	 * @param type Tipo de algoritmo a construir.
	 */
	void select(AlgorithmType type);

	/**
	 * Entrega los parametros procesados para su configuracion.
	 * @param pc Contenedor de parametros.
	 */
	void setParams(ParameterContainer *pc);

	/**
	 * Establece el uso o no de threads dentro del procesamiento.
	 * @param use_threads Usar o no usar threads.
	 */
	void setThreads(bool use_threads);

	/**
	 * Principal funcion a implementar. Se ingresa un puntero a un objeto ParameterContainer con los parametros
	 * necesarios para la ejecucion optima del algoritmo.
	 * @return Vector de MyPeak representando los peaks encontrados dentro de los datos entregados.
	 */
	vector<MyPeak> execute();
};

#endif
