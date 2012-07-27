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
private:
	bool _secondFilterI;
	bool _secondFilterV;
	double _d;
	double _w;
	double _vor_thresh;
	double _vor_areaSL;
	double _FilterI;
	double _FilterV;
	unsigned int _minsep;
	unsigned int _maxIterations;
	unsigned int _chi_cut;
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
	 * Esta variante ejecuta en forma iterativa la deteccion de minimos cuadrados en la diferencia de la imagen contra
	 * la imagen generada a partir de los peaks encontrados, produciendo una mayor deteccion de particulas.
	 * @return Vector de MyPeak representando los peaks encontrados dentro de los datos entregados.
	 */
	vector<MyPeak> run();
};

#endif
