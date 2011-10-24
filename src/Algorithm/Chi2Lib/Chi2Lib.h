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

	static void generateGridImpl(vector<MyPeak> *peaks, unsigned int shift, MyMatrix<double> *img, int x1, int x2, int y1, int y2, MyMatrix<double> *grid_x, MyMatrix<double> *grid_y, MyMatrix<int> *over);
	static void *generateGridThread( void* ptr);

	static void newtonCenterImpl(MyMatrix<int> *over, MyMatrix<double> *diff, vector<MyPeak> *peaks, int init, int end, int shift, double D, double w, double dp, double maxdr);
	static void *newtonCenterThread( void* ptr);
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
	static vector<MyPeak> getPeaks(MyMatrix<double> *img, int threshold, int mindistance, int minsep, bool use_threads = true);

	/**
	 * Genera las matrices auxiliares con valores iguales a las distancias en X e Y al centro de los puntos detectados.
	 */
	static void generateGrid(vector<MyPeak> *peaks, unsigned int shift, MyMatrix<double> *img, MyMatrix<double> *grid_x, MyMatrix<double> *grid_y, MyMatrix<int> *over, bool use_threads = true);

	/**
	 * Calcula la diferencia con la Imagen Chi2 y la Imagen normal
	 */
	static double computeDifference(MyMatrix<double> *img, MyMatrix<double> *grid_x, MyMatrix<double> *grid_y, double d, double w, MyMatrix<double> *diffout, bool use_threads = true);
	static void * computeDifferenceThread( void* ptr);
	/**
	 * Trata de mejorar el centro de las particulas mediante el metodo de newton
	 */
	static void newtonCenter(MyMatrix<int> *over, MyMatrix<double> *diff, vector<MyPeak> *peaks, int shift, double D, double w, double dp, double maxdr = 20.0, bool use_threads = true);

	/**
	 * Traslada los peaks ajustandolos a la imagen (Originalmente Imagen + Margen del tamaño del Kernel)
	 */
	static void translatePeaks(vector<MyPeak> *peaks, unsigned int ss);

	/**
	 * Agrega el estado Solido o Liquido a la particula
	 */
	static void addState(vector<MyPeak> *peaks, double vor_areaSL = 75.0);

	/**
	 * Agrega a los peaks la intensidad de la imagen original.
	 */
	static void addIntensityFromImage(MyMatrix<double> *img, vector<MyPeak> *peaks, unsigned int ss);
};

#endif
