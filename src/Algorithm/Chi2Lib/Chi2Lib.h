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
#include "pthread.h"
#include <cmath>
#include <vector>
#include <algorithm>

#ifndef CHI2LIB
#define CHI2LIB

/**
 * Clase con funciones especificas para ejecutar el algoritmo de minimos cuadrados simple.
 */
class Chi2Lib {
private:
	struct PartitionPeaks{
		vector<MyPeak> *peaks;int init; int end;
		vector<MyPeak> *valids;
		int mindistance;
	};

	struct PartitionGrid{
		vector<MyPeak> *peaks;
		int x1, x2, y1, y2;
		unsigned int shift;
		MyMatrix<double> *img;
		MyMatrix<double> *grid_x;
		MyMatrix<double> *grid_y;
		MyMatrix<int> *over;
	};

	struct PartitionNC{
		vector<MyPeak> *peaks; int i_ini, i_end;
		MyMatrix<int> *over; MyMatrix<double> *diff;
		int shift; double D, w, dp, maxdr;
	};

	struct PartitionDiff{
		MyMatrix<double> *img;
		unsigned int x1, x2, y1, y2;
		MyMatrix<double> *grid_x;
		MyMatrix<double> *grid_y;
		double d, w;
		double err;
		MyMatrix<double> *diffout;
	};
	/**
	 * Verifica si un punto es minimo local
	 */
	static bool findLocalMinimum(MyMatrix<double> *img, unsigned int imgX, unsigned int imgY, int minsep);

	/**
	 * Valida los minimos segun una minima distancia
	 */
	static void validatePeaks(vector<MyPeak> *peaks, int init, int end, int mindistance, vector<MyPeak> *valids);
	static void *validatePeaksThread( void* ptr);

	static void * computeDifferenceThread( void* ptr);

	static void generateGridImpl(vector<MyPeak> *peaks, unsigned int shift, MyMatrix<double> *img, int x1, int x2, int y1, int y2, MyMatrix<double> *grid_x, MyMatrix<double> *grid_y, MyMatrix<int> *over);
	static void *generateGridThread( void* ptr);

	static void newtonCenterImpl(MyMatrix<int> *over, MyMatrix<double> *diff, vector<MyPeak> *peaks, int init, int end, int shift, double D, double w, double dp, double maxdr);
	static void *newtonCenterThread( void* ptr);
public:
	/**
	 * Obtiene los valores maximos y minimos (en orden) de una matriz
	 * @param mtrx Matriz en la cual detectar Maximo y Minimo.
	 * @return Par de valores Maximo y Minimo de la matriz, en orden.
	 */
	static pair<double, double> getHighLow(MyMatrix<double> *mtrx);

	/**
	 * Normaliza la imágen segun los valores máximo y mínimo ingresado.
	 * @param mtrx Matriz a normalizar
	 * @param maximum Valor Maximo entregado, si no se entrega se detecta.
	 * @param minimum Valor Minimo entregado, si no se entrega se detecta.
	 */
	static void normalizeImage(MyMatrix<double> *mtrx, double maximum = -1, double minimum = -1);

	/**
	 * Obtener imagen de una particula ideal a partir de una funcion de particula idealizada.
	 * @param ss Tamaño de la particula ideal.
	 * @param os Tamaño /2 de la particula
	 * @param d Diametro de la particula ideal.
	 * @param w Peso de la particula, este valor depende del foco de la imagen.
	 * @return Matriz representando una particula ideal.
	 */
	static MyMatrix<double> generateKernel(unsigned int ss, unsigned int os, double d, double w);

	/**
	 * Obentiene los minimos locales validos dentro una imagen chi2, detectando asi, los peaks.
	 * @param img Matriz de imagen en donde detectar los peaks.
	 * @param threshold Tolerancia minima aceptable de intensidad de imagen para detectar un peak.
	 * @param mindistance Area minima aceptable para considerar un peak valido como minimo local.
	 * @param minsep Separacion Minima aceptable entre un peak y otro para ser considerado valido.
	 * @param use_threads ejecucion de la funcion usando Threads.
	 * @return Vector de MyPeaks detectados.
	 */
	static vector<MyPeak> getPeaks(MyMatrix<double> *img, double threshold, int mindistance, int minsep, bool use_threads = true);

	/**
	 * Genera las matrices auxiliares con valores iguales a las distancias en X e Y al centro de los peaks detectados.
	 * @param peaks Peaks detectados.
	 * @param shift correccion de posicion para los peaks dentro de la imagen original. (Peaks tienen posiciones en la imagen Chi2).
	 * @param img Imagen original de la deteccion de peaks.
	 * @param grid_x Matriz donde guardar las posiciones de X al centro del peak mas cercano.
	 * @param grid_y Matriz donde guardar las posiciones de Y al centro del peak mas cercano.
	 * @param over Matriz donde guardar los indices dentro del vector de peaks de los peaks mas cercanos.
	 * @param use_threads ejecucion de la funcion usando Threads.
	 */
	static void generateGrid(vector<MyPeak> *peaks, unsigned int shift, MyMatrix<double> *img, MyMatrix<double> *grid_x, MyMatrix<double> *grid_y, MyMatrix<int> *over, bool use_threads = true);

	/**
	 * Calcula la diferencia de la Imagen Chi2 generada a partir de los peaks detectados y la Imagen normal.
	 * @param img Imagen original de la deteccion de peaks.
	 * @param grid_x Posiciones de X al centro del peak mas cercano.
	 * @param grid_y Posiciones de Y al centro del peak mas cercano.
	 * @param d Diametro de la particula ideal.
	 * @param w Peso de la particula, este valor depende del foco de la imagen.
	 * @param diffout Matriz donde guardar la diferencia.
	 * @param use_threads ejecucion de la funcion usando Threads.
	 * @return valor del error cuadrado.
	 */
	static double computeDifference(MyMatrix<double> *img, MyMatrix<double> *grid_x, MyMatrix<double> *grid_y, double d, double w, MyMatrix<double> *diffout, bool use_threads = true);

	/**
	 * Trata de mejorar el centro de las particulas mediante el metodo de newton.
	 * @param over Matriz de indices dentro del vector de peaks de los peaks mas cercanos.
	 * @param diff Matriz de diferencia entre Imagen original y generada a partir de los Peaks.
	 * @param peaks Peaks detectados actualmente.
	 * @param shift correccion de posicion para los peaks dentro de la imagen original. (Peaks tienen posiciones en la imagen Chi2).
	 * @param d Diametro de la particula ideal.
	 * @param w Peso de la particula, este valor depende del foco de la imagen.
	 * @param dp
	 * @param maxdr Valor Maximo para considerar la nueva posicion admisible.
	 * @param use_threads ejecucion de la funcion usando Threads.
	 */
	static void newtonCenter(MyMatrix<int> *over, MyMatrix<double> *diff, vector<MyPeak> *peaks, int shift, double D, double w, double dp, double maxdr = 20.0, bool use_threads = true);

	/**
	 * Traslada los peaks ajustandolos a la imagen (Imagen Original - Margen del tamaño del Kernel)
	 * @param peaks Peaks detectados actualmente.
	 * @param ss Tamaño de la particula ideal.
	 */
	static void translatePeaks(vector<MyPeak> *peaks, unsigned int ss);

	/**
	 * Agrega el estado Solido o Liquido a la particula segun el corte de area de voronoi.
	 * @param peaks Peaks detectados actualmente.
	 * @param vor_areaSL Corte entre solido y liquido.
	 */
	static void addState(vector<MyPeak> *peaks, double vor_areaSL = 75.0);

	/**
	 * Agrega a los peaks la intensidad de la imagen original.
	 * @param img Imagen original de la deteccion de peaks.
	 * @param peaks Peaks detectados actualmente.
	 * @param ss Tamaño de la particula ideal. (Para hacer la correccion de posicion)
	 */
	static void addIntensityFromImage(MyMatrix<double> *img, vector<MyPeak> *peaks, unsigned int ss);
};

#endif
