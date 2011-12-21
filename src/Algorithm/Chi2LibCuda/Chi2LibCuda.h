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

class Chi2LibCuda {
private:
	/**
	 * Convierte los MyPeaks de un vector a un arreglo de cuMyPeak
	 */
	static cuMyPeakArray convertPeaks(vector<MyPeak>* peaks);

	struct GridPartition{
		cuMyPeakArray *peaks;
		int x1, x2, y1, y2;
		unsigned int shift;
		cuMyMatrix *grid_x;
		cuMyMatrix *grid_y;
		cuMyMatrixi *over;
	};

public:
	/**
	 * Establece los valores necesarios dentro del dispositivo acorde a los datos entregados
	 */
	static cuMyMatrix initializeData(MyMatrix<double>* data);

	/**
	 * Obtiene los valores maximos y minimos (en orden) de una matriz
	 */
	static pair<float, float> getHighLow(cuMyMatrix* arr);

	/**
	 * Normaliza la imágen y retorna el valor máximo y mínimo una vez normalizado.
	 */
	static void normalizeImage(cuMyMatrix* arr, float maximum = -1, float minimum = -1);

	/**
	 * Obtener imagen de la particula ideal
	 */
	static cuMyMatrix generateKernel(unsigned int ss, unsigned int os, float d, float w);

	/**
	 * Obtiene los Peaks de la imagen
	 */
	static cuMyPeakArray getPeaks(cuMyMatrix* arr, int threshold, int mindistance, int minsep, bool validate = true);

	/**
	 * Copia los Peaks en CUDA y los pasa a vector
	 */
	static vector<MyPeak> convert(cuMyPeakArray* peaks);

	/**
	 * Genera las matrices auxiliares
	 */
	static void generateGrid(cuMyPeakArray* peaks, unsigned int shift, cuMyMatrix* grid_x, cuMyMatrix* grid_y, cuMyMatrixi* over);

	/**
	 * Calcula la diferencia entre la Imagen Chi2 y la Imagen normal
	 */
	static float computeDifference(cuMyMatrix *img, cuMyMatrix *grid_x, cuMyMatrix *grid_y, float d, float w, cuMyMatrix *diffout);

	/**
	 * Trata de mejorar el centro de las particulas mediante el metodo de newton
	 */
	static void newtonCenter(cuMyMatrixi *over, cuMyMatrix *diff, cuMyPeakArray *peaks, int shift, double D, double w, double dp, double maxdr = 20.0);

	/**
	 * Traslada los Peaks a su posicion correcta
	 */
	static void translatePeaks(cuMyPeakArray *peaks, unsigned int ss);

	/**
	 * Establece el limite de Peaks entre solido y liquido
	 */
	static void addState(cuMyPeakArray *peaks, float vor_areaSL);
};

#endif /* CHI2LIBCUDA_H_ */
