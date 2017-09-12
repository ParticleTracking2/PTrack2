/*
 * Chi2LibHighDensity.h
 *
 *  Created on: 03/10/2011
 *      Author: ptrack
 */

#include <vector>
#include "Chi2Lib.h"
#include "Chi2LibQhull.h"
#include "../MyPeak.h"
#include "../../Utils/MyLogger.h"
#include "../../Container/MyMatrix.h"

#ifndef CHI2LIBHIGHDENSITY
#define CHI2LIBHIGHDENSITY

/**
 * Clase con funciones especificas para ejecutar el algoritmo de minimos cuadrados con alta densidad de particulas.
 */
class Chi2LibHighDensity {
public:

	/**
	 * Escala la Imagen elevandola al cuadrado y multiplicandola por 4.
	 * @param diff Imagen base.
	 * @param out Matriz de imagen de salida.
	 */
	static double generateScaledImage(MyMatrix<double> *diff, MyMatrix<double> *out);

	/**
	 * Chequea si los Peaks encontrados se ubican en el interior de la imagen y los agrega al antiguo vector de peaks.
	 * @param old_peaks Vector de peaks antiguo.
	 * @param new_peaks Vector de peaks nuevos.
	 * @param img Imagen original.
	 * @param os Tamaño /2 de la particula ideal.
	 */
	static unsigned int checkInsidePeaks(vector<MyPeak> *old_peaks, vector<MyPeak> *new_peaks, MyMatrix<double> *img, unsigned int os);

	/**
	 * Elimina los peaks que se encuentran fuera de la imagen (Recuerdo: los peaks encontrados pueden estar fuera de la imagen original)
	 * @param peaks Vector de peaks detectados.
	 * @param img Imagen original.
	 * @param ss Tamaño /2 de la particula ideal.
	 */
	static void filterPeaksOutside(vector<MyPeak> *peaks, MyMatrix<double> *img, unsigned int ss);

	/**
	 * Encuantra los parametros Mu y Sigma para un ajuste gausiano.
	 * @param peaks Vector de peaks detectados.
	 * @param img Imagen original.
	 * @param ss Tamaño /2 de la particula ideal.
	 * @return Par de datos Mu y Sigma respectivamente.
	 */
	static pair<double,double> gaussianFit(vector<MyPeak> *peaks, MyMatrix<double> *img, unsigned int ss);

	/**
	 * Elimina los Peaks con una area de Voronoi y una intensidad de imagen bajo lo tolerable.
	 * @param peaks Vector de peaks detectados.
	 * @param img Imagen original.
	 * @param vor_threshold Area de voronoi minima tolerable.
	 * @param par_threshold Intensidad de imagen minima tolerable.
	 * @param ss Tamaño /2 de la particula ideal.
	 */
	static void removeBadPeaks(vector<MyPeak> *peaks, MyMatrix<double> *img, double vor_threshold, double par_threshold, unsigned int ss);

	/**
	 * Elimina los Peaks con una intensidad de imagen bajo lo tolerable.
	 * @param peaks Vector de peaks detectados.
	 * @param img Imagen original.
	 * @param par_threshold Intensidad de imagen minima tolerable.
	 * @param ss Tamaño /2 de la particula ideal.
	 */
	static void removeBadIntensityPeaks(vector<MyPeak> *peaks, MyMatrix<double> *img, double par_threshold, unsigned int ss);

	/**
	 * Elimina los Peaks con una area de Voronoi bajo lo tolerable.
	 * @param peaks Vector de peaks detectados.
	 * @param img Imagen original.
	 * @param vor_threshold Area de voronoi minima tolerable.
	 * @param ss Tamaño /2 de la particula ideal.
	 */
	static void removeBadVoronoiPeaks(vector<MyPeak> *peaks, MyMatrix<double> *img, double vor_threshold, unsigned int ss);
};

#endif
