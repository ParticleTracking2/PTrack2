/*
 * Chi2LibCudaHighDensity.h
 *
 *  Created on: 13/12/2011
 *      Author: juanin
 */

#ifdef CHI2CUDA
#include "Container/cuMyMatrix.h"
#include "Chi2LibcuHighDensity.h"
#include "../../Utils/MyLogger.h"
#include "../Chi2LibCuda/Chi2LibCuda.h"

#ifndef CHI2LIBCUDAHIGHDENSITY_H_
#define CHI2LIBCUDAHIGHDENSITY_H_

/**
 * Clase con funciones especificas para ejecutar el algoritmo de minimos cuadrados con alta densidad de particulas.
 * La mayoria de las funciones y estructuras de datos se ejecutan y residen en GPU.
 */
class Chi2LibCudaHighDensity {
public:

	/**
	 * Escala la Imagen elevandola al cuadrado y multiplicandola por 4.
	 * @param diff Imagen base.
	 * @param out Matriz de imagen de salida.
	 */
	static double generateScaledImage(cuMyMatrix *diff, cuMyMatrix *out);

	/**
	 * Chequea si los Peaks encontrados se ubican en el interior de la imagen y los agrega al antiguo contenedor.
	 * @param old_peaks Contenedor de peaks antiguo en GPU.
	 * @param new_peaks Contenedor de peaks nuevos en GPU.
	 * @param img Imagen original.
	 * @param os Tamaño /2 de la particula ideal.
	 * @return Cantidad de peaks nuevos agregados al contenedor antiguo.
	 */
	static unsigned int checkInsidePeaks(cuMyPeakArray *old_peaks, cuMyPeakArray *new_peaks, cuMyMatrix *img, unsigned int os);

	/**
	 * Filtra los Peaks que se encuentran afuera de la imagen original.
	 * @param peaks Contenedor de peaks en GPU.
	 * @param img Imagen original.
	 * @param os Tamaño /2 de la particula ideal.
	 */
	static void filterPeaksOutside(cuMyPeakArray *peaks, cuMyMatrix *img, unsigned int os);

	/**
	 * Encuantra los parametros Mu y Sigma para un ajuste gausiano
	 * @param peaks Contenedor de peaks en GPU.
	 * @param img Imagen original.
	 * @param ss Tamaño /2 de la particula ideal.
	 * @return Par de datos Mu y Sigma respectivamente.
	 */
	static pair<double, double> gaussianFit(cuMyPeakArray *peaks, cuMyMatrix *img, unsigned int ss);

	/**
	 * Elimina los Peaks con una area de Voronoi y una intensidad de imagen bajo lo tolerable.
	 * @param peaks Contenedor de peaks en GPU.
	 * @param img Imagen original.
	 * @param vor_threshold Area de voronoi minima tolerable.
	 * @param par_threshold Intensidad de imagen minima tolerable.
	 * @param ss Tamaño /2 de la particula ideal.
	 */
	static void removeBadPeaks(cuMyPeakArray *peaks, cuMyMatrix *img, double vor_threshold, double par_threshold, unsigned int ss);

	/**
	 * Elimina los Peaks con una intensidad de imagen bajo lo tolerable.
	 * @param peaks Contenedor de peaks en GPU.
	 * @param img Imagen original.
	 * @param par_threshold Intensidad de imagen minima tolerable.
	 * @param ss Tamaño /2 de la particula ideal.
	 */
	static void removeBadIntensityPeaks(cuMyPeakArray *peaks, cuMyMatrix *img, double par_threshold, unsigned int ss);

	/**
	 * Elimina los Peaks con una area de Voronoi bajo lo tolerable.
	 * @param peaks Contenedor de peaks en GPU.
	 * @param img Imagen original.
	 * @param vor_threshold Area de voronoi minima tolerable.
	 * @param ss Tamaño /2 de la particula ideal.
	 */
	static void removeBadVoronoiPeaks(cuMyPeakArray *peaks, cuMyMatrix *img, double vor_threshold, unsigned int ss);
};

#endif /* CHI2LIBCUDAHIGHDENSITY_H_ */
#endif
