/*
 * Chi2LibCuda.h
 *
 *  Created on: 18/11/2011
 *      Author: juanin
 */

#ifndef CHI2LIBCUDA_H_
#define CHI2LIBCUDA_H_

#include <cmath>
#include "Chi2HD_Cuda.h"
#include "../../Utils/MyLogger.h"
#include "../../Container/MyMatrix.h"

class Chi2LibCuda {
public:
	/**
	 * Establece los valores necesarios dentro del dispositivo acorde a los datos entregados
	 */
	static cuMyArray2D initializeData(MyMatrix<double>* data);

	/**
	 * Obtiene los valores maximos y minimos (en orden) de una matriz
	 */
	static pair<float, float> getHighLow(cuMyArray2D* arr);

	/**
	 * Normaliza la imágen y retorna el valor máximo y mínimo una vez normalizado.
	 */
	static void normalizeImage(cuMyArray2D* arr, double maximum = -1, double minimum = -1);

	/**
	 * Obtener imagen de la particula ideal
	 */
	static cuMyArray2D generateKernel(unsigned int ss, unsigned int os, double d, double w);
};

#endif /* CHI2LIBCUDA_H_ */
