/*
 * Chi2HDCudaAlgorithm.h
 *
 *  Created on: 15-11-2011
 *      Author: ptrack
 */

#ifdef CHI2CUDA
#ifndef CHI2HDCUDAALGORITHM
#define CHI2HDCUDAALGORITHM

#include "../Algorithm.h"
#include "../../Utils/FileUtils.h"
#include "../Chi2Lib/Chi2Lib.h"
#include "../Chi2LibCuda/Chi2LibCuda.h"
#include "../Chi2LibCuda/Chi2LibCudaFFT.h"
#include "../Chi2LibCuda/Chi2LibCudaQhull.h"
#include "../Chi2LibCuda/Chi2LibCudaFFTCache.h"
#include "../Chi2LibCuda/Chi2LibCudaHighDensity.h"
#include "Container/cuMyMatrix.h"
#include "Container/cuMyPeak.h"

using namespace std;

/**
 * Implementacion de algoritmo Chi Cuadrado para imagenes con alta densidad de particulas.
 * Esta variante se ejecuta usando GPU con tecnologia NVIDIA CUDA.
 */
class Chi2HDCudaAlgorithm: public Algorithm {
private:
	bool _secondFilterI;
	bool _secondFilterV;
	bool _validateOnes;
	bool _cuda;
	int _cudaDev;
	float _d;
	float _w;
	float _vor_thresh;
	float _vor_areaSL;
	float _FilterI;
	float _FilterV;
	unsigned int _minsep;
	unsigned int _maxIterations;
	unsigned int _chi_cut;
	cuMyMatrix cuImg;
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
	 * Ejecuta el algoritmo de minimos cuadrados para detectar Peaks usando GPU.
	 * Esta variante ejecuta en forma iterativa la deteccion de minimos cuadrados en la diferencia de la imagen contra
	 * la imagen generada a partir de los peaks encontrados, produciendo una mayor deteccion de particulas.
	 * @param pc Parametros que ocupa el algoritmo para correr.
	 * @return Vector de MyPeak representando los peaks encontrados dentro de los datos entregados.
	 */
	vector<MyPeak> run();
};

#endif
#endif
