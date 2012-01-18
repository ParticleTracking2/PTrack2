/*
 * Chi2Algorithm.h
 *
 *  Created on: 12-06-2011
 *      Author: juanin
 */

#ifndef CHI2ALGORITHM
#define CHI2ALGORITHM
#include "../Algorithm.h"
#include "../Chi2Lib/Chi2Lib.h"
#include "../Chi2Lib/Chi2LibQhull.h"
#include "../Chi2Lib/Chi2LibMatrix.h"
#include "../Chi2Lib/Chi2LibFFTW.h"

using namespace std;

/**
 * Implementacion de algoritmo Chi Cuadrado.
 */
class Chi2Algorithm: public Algorithm {
private:
	double _d;
	double _w;
	unsigned int _maxIterations;
	MyMatrix<double> _data;
public:

	/**
	 * Devuelve los parametros que acepta este Algoritmo.
	 * @return Todos los parametros que acepta este algoritmo para ejecutar.
	 */
	static ArgObj myArgs();

	/**
	 * Establece los datos para ser procesados.
	 * @param pc Parametros que ocupa el algoritmo para correr.
	 */
	void setData(ParameterContainer *pc);

	/**
	 * Ejecuta el algoritmo de minimos cuadrados para detectar Peaks.
	 * @return Vector de MyPeak representando los peaks encontrados dentro de los datos entregados.
	 */
	vector<MyPeak> run();
};

#endif
