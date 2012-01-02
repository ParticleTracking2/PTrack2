/*
 * Chi2LibFFTW.h
 *
 *  Created on: 02/10/2011
 *      Author: juanin
 */
#include <cmath>
#include "../../Container/MyMatrix.h"
#include "../../Utils/MyLogger.h"
#include "../../Utils/FileUtils.h"
#include <fftw3.h>
#include "Chi2LibMatrix.h"
#include "Chi2LibFFTWCache.h"

#ifndef CHI2LIBFFTW
#define CHI2LIBFFTW

/**
 * Clase para realizar convolucion de imagen mediante FFTW.
 * Esta clase ocupa FFTW probado y funcionando en version 3.3.
 * Además para evitar reserva y liberacion de memoria constantemente, usa Cache de datos.
 * Para evitar calculos redundantes, estos se calculan una sola vez y se almacenan para posterior uso.
 * En su primer uso se ejecutan 3 Threads de FFTW y luego solo se ejecutan 2 pues un resultado es constante.
 */
class Chi2LibFFTW {
private:

	/**
	 * Particion de datos para ejecucion en multiples Threads.
	 */
	struct PartitionFFT{
		MyMatrix<double> *img;
		MyMatrix<double> *kernel_img;
		MyMatrix<double> *output;
	};

	/**
	 * Elementos del cache de datos.
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

	/**
	 * Mutex necesario para establecer datos dentro de FFTW.
	 */
	static pthread_mutex_t mutex1;

	/**
	 * Hace el enlace de los threads hacia la funcion conv2d_fft
	 * @param ptr Puntero a PartitionFFT.
	 */
	static void *conv2d_fftThread(void *ptr);

	/**
	 * Ejecuta una convolucion de una Imagen y una imagen ideal ambas representada por una Matriz de double.
	 * Almacena la salida en una Matriz de tamaño aumentado por la imagen ideal.
	 * @param img Imagen en la cual hacer convolucion.
	 * @param kernel_img Imagen de particula ideal.
	 * @param output Matriz de salida de datos de convolucion.
	 */
	static void conv2d_fft(MyMatrix<double> *img, MyMatrix<double> *kernel_img, MyMatrix<double> *output);
public:

	/**
	 * Obtiene una Imagen Chi2 a partir de un trio de imagenes de convolucion.
	 * @param kernel Imagen de particula ideal.
	 * @param img Imagen original en base a la cual generar la imagen Chi2.
	 * @param out Imagen Chi2 generada a partir de los datos.
	 * @param use_thread Establece el uso de Threads para acelerar el procesamiento.
	 */
	static void getChiImage(MyMatrix<double> *kernel, MyMatrix<double> *img, MyMatrix<double> *out, bool use_thread = true);
};

#endif
