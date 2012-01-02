/*
 * Chi2LibCudaFFT.h
 *
 *  Created on: 21-11-2011
 *      Author: ptrack
 */

#ifndef CHI2LIBCUDAFFT_H_
#define CHI2LIBCUDAFFT_H_

#include "Container/cuMyMatrix.h"
#include "Chi2LibcuMatrix.h"
#include "Chi2LibcuFFT.h"

#include "../../Utils/MyLogger.h"
#include "Chi2LibCudaFFTCache.h"

/**
 * Clase para realizar convolucion de imagen mediante cuFFT.
 * Esta clase ocupa cuFFTW probado y funcionando en version de API 4.0.
 * Además para evitar reserva y liberacion de memoria constantemente, usa Cache de datos.
 * Para evitar calculos redundantes, estos se calculan una sola vez y se almacenan para posterior uso.
 * En su primer uso se ejecutan 3 calculos de cuFFT y luego solo se ejecutan 2 pues un resultado es constante.
 */
class Chi2LibCudaFFT {
private:
	/**
	 * Enumeracion de los elementos a usar del cache, para un mejor entendimiento.
	 */
	enum cached{
		cached_kernel = 0,
		cached_kernel2 = 1,
		cached_kernel3 = 2,
		cached_blank = 3,
		cached_first_term = 4,
		cached_second_term = 5,
		cached_third_term = 6
	};
public:

	/**
	 * Obtiene una Imagen Chi2 a partir de un trio de imagenes de convolucion.
	 * @param kernel Imagen de particula ideal.
	 * @param img Imagen original en base a la cual generar la imagen Chi2.
	 * @param out Imagen Chi2 generada a partir de los datos.
	 */
	static void getChiImage(cuMyMatrix *kernel, cuMyMatrix *img, cuMyMatrix *out);
};

#endif /* CHI2LIBCUDAFFT_H_ */
