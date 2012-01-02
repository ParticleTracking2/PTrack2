/*
 * Chi2LibCuda.h
 *
 *  Created on: 18/11/2011
 *      Author: juanin
 */

#ifndef CHI2LIBCUDA_H_
#define CHI2LIBCUDA_H_

#include <cmath>
#include "Container/cuMyMatrix.h"
#include "Chi2Libcu.h"
#include "../Chi2Lib/Chi2Lib.h"
#include "Container/cuMyPeak.h"

#include "../MyPeak.h"
#include "../../Utils/MyLogger.h"
#include "../../Container/MyMatrix.h"

/**
 * Clase con funciones especificas para ejecutar el algoritmo de minimos cuadrados simple.
 * La mayoria de las funciones y estructuras de datos se ejecutan y residen en GPU.
 */
class Chi2LibCuda {
private:

	/**
	 * Convierte los MyPeaks de un vector a un contenedor de cuMyPeak
	 * @param peaks Vector de MyPeaks.
	 * @param Arreglo de cuMyPeaks que se pueden trabajar en GPU.
	 */
	static cuMyPeakArray convertPeaks(vector<MyPeak>* peaks);

public:

	/**
	 * Convierte una Matriz de datos de tipo MyMatrix a una cuMyMatrix en la cual se puede trabajar en GPU.
	 * @param data Matriz de datos en CPU.
	 */
	static cuMyMatrix initializeData(MyMatrix<double>* data);

	/**
	 * Obtiene los valores maximos y minimos (en orden) de una matriz en GPU.
	 * @param mtrx Matriz en la cual detectar Maximo y Minimo.
	 * @return Par de valores Maximo y Minimo de la matriz, en orden.
	 */
	static pair<float, float> getHighLow(cuMyMatrix* arr);

	/**
	 * Normaliza la imágen segun los valores máximo y mínimo ingresado.
	 * @param arr Matriz a normalizar
	 * @param maximum Valor Maximo entregado, si no se entrega se detecta.
	 * @param minimum Valor Minimo entregado, si no se entrega se detecta.
	 */
	static void normalizeImage(cuMyMatrix* arr, float maximum = -1, float minimum = -1);

	/**
	 * Obtiene una imagen de una particula ideal a partir de una funcion de particula idealizada.
	 * @param ss Tamaño de la particula ideal.
	 * @param os Tamaño /2 de la particula
	 * @param d Diametro de la particula ideal.
	 * @param w Peso de la particula, este valor depende del foco de la imagen.
	 * @return Matriz en GPU representando una particula ideal.
	 */
	static cuMyMatrix generateKernel(unsigned int ss, unsigned int os, float d, float w);

	/**
	 * Obentiene los minimos locales validos dentro una imagen chi2, detectando asi, los peaks.
	 * @param arr Matriz de imagen en donde detectar los peaks.
	 * @param threshold Tolerancia minima aceptable de intensidad de imagen para detectar un peak.
	 * @param mindistance Area minima aceptable para considerar un peak valido como minimo local.
	 * @param minsep Separacion Minima aceptable entre un peak y otro para ser considerado valido.
	 * @param validate Ejecuta la validacion de los Peaks en el momento(True) o se dejan para despues (False).
	 * @return Contenedor de cuMyPeaks detectados en GPU.
	 */
	static cuMyPeakArray getPeaks(cuMyMatrix* arr, int threshold, int mindistance, int minsep, bool validate = true);

	/**
	 * Copia los Peaks en CUDA y los pasa a vector de MyPeaks.
	 * @param peaks Contenedor de Peaks en GPU.
	 * @return Vector de MyPeaks.
	 */
	static vector<MyPeak> convert(cuMyPeakArray* peaks);

	/**
	 * Genera las matrices auxiliares con valores iguales a las distancias en X e Y al centro de los peaks detectados.
	 * @param peaks Contenedor de Peaks detectados en GPU.
	 * @param shift correccion de posicion para los peaks dentro de la imagen original. (Peaks tienen posiciones en la imagen Chi2).
	 * @param grid_x Matriz en GPU donde guardar las posiciones de X al centro del peak mas cercano.
	 * @param grid_y Matriz en GPU donde guardar las posiciones de Y al centro del peak mas cercano.
	 * @param over Matriz en GPU donde guardar los indices dentro del vector de peaks de los peaks mas cercanos.
	 */
	static void generateGrid(cuMyPeakArray* peaks, unsigned int shift, cuMyMatrix* grid_x, cuMyMatrix* grid_y, cuMyMatrixi* over);

	/**
	 * Calcula la diferencia de la Imagen Chi2 generada a partir de los peaks detectados y la Imagen normal.
	 * @param img Imagen original de la deteccion de peaks.
	 * @param grid_x Posiciones de X al centro del peak mas cercano.
	 * @param grid_y Posiciones de Y al centro del peak mas cercano.
	 * @param d Diametro de la particula ideal.
	 * @param w Peso de la particula, este valor depende del foco de la imagen.
	 * @param diffout Matriz donde guardar la diferencia.
	 * @return valor del error cuadrado.
	 */
	static float computeDifference(cuMyMatrix *img, cuMyMatrix *grid_x, cuMyMatrix *grid_y, float d, float w, cuMyMatrix *diffout);

	/**
	 * Trata de mejorar el centro de las particulas mediante el metodo de newton.
	 * @param over Matriz de indices dentro del vector de peaks de los peaks mas cercanos.
	 * @param diff Matriz de diferencia entre Imagen original y generada a partir de los Peaks.
	 * @param peaks Peaks detectados actualmente en GPU.
	 * @param shift correccion de posicion para los peaks dentro de la imagen original. (Peaks tienen posiciones en la imagen Chi2).
	 * @param d Diametro de la particula ideal.
	 * @param w Peso de la particula, este valor depende del foco de la imagen.
	 * @param dp
	 * @param maxdr Valor Maximo para considerar la nueva posicion admisible.
	 */
	static void newtonCenter(cuMyMatrixi *over, cuMyMatrix *diff, cuMyPeakArray *peaks, int shift, double D, double w, double dp, double maxdr = 20.0);

	/**
	 * Traslada los peaks ajustandolos a la imagen (Imagen Original - Margen del tamaño del Kernel)
	 * @param peaks Peaks detectados actualmente en GPU.
	 * @param ss Tamaño de la particula ideal.
	 */
	static void translatePeaks(cuMyPeakArray *peaks, unsigned int ss);

	/**
	 * Agrega el estado Solido o Liquido a la particula segun el corte de area de voronoi.
	 * @param peaks Peaks detectados actualmente en GPU.
	 * @param vor_areaSL Corte entre solido y liquido.
	 */
	static void addState(cuMyPeakArray *peaks, float vor_areaSL);
};

#endif /* CHI2LIBCUDA_H_ */
