/*
 * Chi2Lib.h
 *
 *  Created on: 02/10/2011
 *      Author: juanin
 */
#include "../../Container/MyMatrix.h"
#include "../../Utils/MyLogger.h"
#include "../../Utils/FileUtils.h"
#include "../MyPeak.h"
#include "Chi2LibMatrix.h"
#include <cmath>
#include <vector>
#include <algorithm>

#ifndef CHI2LIB
#define CHI2LIB

class Chi2Lib {
public:
	/**
	 * Obtiene los valores maximos y minimos (en orden) de una matriz
	 */
	static pair<double, double> getHighLow(MyMatrix<double> *mtrx);

	/**
	 * Normaliza la imágen y retorna el valor máximo y mínimo una vez normalizado.
	 */
	static void normalizeImage(MyMatrix<double> *mtrx, double maximum = -1, double minimum = -1);

	/**
	 * Obtener imagen de la particula ideal
	 */
	static MyMatrix<double> generateKernel(unsigned int ss, unsigned int os, double d, double w);

	/**
	 * Obentiene los minimo locales validos dentro de la imagen
	 */
	static vector<MyPeak> getPeaks(MyMatrix<double> *img, int threshold, int mindistance, int minsep);

	/**
	 * Verifica si un punto es minimo local
	 */
	static bool findLocalMinimum(MyMatrix<double> *img, unsigned int imgX, unsigned int imgY, int minsep);

	/**
	 * Valida los minimos segun una minima distancia
	 */
	static void validatePeaks(vector<MyPeak> *peaks, int mindistance);

	/**
	 * Genera las matrices auxiliares con valores iguales a las distancias en X e Y al centro de los puntos detectados.
	 */
	static void generateGrid(vector<MyPeak> *peaks, unsigned int shift, MyMatrix<double> *img, MyMatrix<double> *grid_x, MyMatrix<double> *grid_y, MyMatrix<int> *over);

	/**
	 * Calcula la diferencia con la Imagen Chi2 y la Imagen normal
	 */
	static double computeDifference(MyMatrix<double> *img, MyMatrix<double> *grid_x, MyMatrix<double> *grid_y, double d, double w, MyMatrix<double> *diffout);
//
//	/**
//	 * Aloja las coordenadas X e Y de los Peaks en dos vectores aparte
//	 */
//	static void setCoordenatesTo(vector<MyPeak> *peaks, vector<double> *px, vector<double> *py);

	/**
	 * Trata de mejorar el centro de las particulas mediante el metodo de newton
	 */
	static void newtonCenter(MyMatrix<int> *over, MyMatrix<double> *diff, vector<MyPeak> *peaks, int shift, double D, double w, double dp, double maxdr = 20.0);

	/**
	 * Transforma las coordenadas para ser leidas en Matlab
	 */
	static void transformPeaks(vector<MyPeak> *peaks, unsigned int ss, unsigned int width, double vor_areaSL = 50.0);
};

#endif