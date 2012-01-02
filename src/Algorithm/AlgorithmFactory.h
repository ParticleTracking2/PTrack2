/*
 * AlgorithmFactory.h
 *
 *  Created on: 11/10/2011
 *      Author: juanin
 */
#include <string>
#include "../Utils/MyLogger.h"
#include "Algorithm.h"
#include "Implementations/Chi2Algorithm.h"
#include "Implementations/Chi2HDAlgorithm.h"
#include "Implementations/Chi2HDCudaAlgorithm.h"

#ifndef ALGORITHMFACTORY
#define ALGORITHMFACTORY

using namespace std;

/**
 * Clase Factory para construir algoritmos segun su tipo.
 */
class AlgorithmFactory {
public:

	/**
	 * Construye un algoritmo segun el tipo entregado.
	 * @param type Tipo de algoritmo a construir.
	 * @return Algoritmo construido.
	 */
	static Algorithm *select(AlgorithmType type);
};

#endif
