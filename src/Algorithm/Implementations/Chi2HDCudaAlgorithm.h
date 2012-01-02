/*
 * Chi2HDCudaAlgorithm.h
 *
 *  Created on: 15-11-2011
 *      Author: ptrack
 */

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
public:

	/**
	 * Ejecuta el algoritmo de minimos cuadrados para detectar Peaks usando GPU.
	 * Esta variante ejecuta en forma iterativa la deteccion de minimos cuadrados en la diferencia de la imagen contra
	 * la imagen generada a partir de los peaks encontrados, produciendo una mayor deteccion de particulas.
	 * @param pc Parametros que ocupa el algoritmo para correr.
	 * @return Vector de MyPeak representando los peaks encontrados dentro de los datos entregados.
	 */
	vector<MyPeak> run(ParameterContainer *pc);
};

#endif
