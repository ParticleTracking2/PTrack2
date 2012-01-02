/*
 * Chi2Algorithm.h
 *
 *  Created on: 12-06-2011
 *      Author: juanin
 */

#include "../Algorithm.h"
#include "../Chi2Lib/Chi2Lib.h"
#include "../Chi2Lib/Chi2LibHighDensity.h"
#include "../Chi2Lib/Chi2LibMatrix.h"
#include "../Chi2Lib/Chi2LibFFTW.h"
#include "../Chi2Lib/Chi2LibFFTWCache.h"

#ifndef CHI2HDALGORITHM
#define CHI2HDALGORITHM

using namespace std;

/**
 * Implementacion de algoritmo Chi Cuadrado para imagenes con alta densidad de particulas.
 */
class Chi2HDAlgorithm: public Algorithm {
public:

	/**
	 * Ejecuta el algoritmo de minimos cuadrados para detectar Peaks.
	 * Esta variante ejecuta en forma iterativa la deteccion de minimos cuadrados en la diferencia de la imagen contra
	 * la imagen generada a partir de los peaks encontrados, produciendo una mayor deteccion de particulas.
	 * @param pc Parametros que ocupa el algoritmo para correr.
	 * @return Vector de MyPeak representando los peaks encontrados dentro de los datos entregados.
	 */
	vector<MyPeak> run(ParameterContainer *pc);
};

#endif
