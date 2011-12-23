/*
 * Chi2LibCudaQhull.h
 *
 *  Created on: 15/12/2011
 *      Author: juanin
 */

#ifndef CHI2LIBCUDAQHULL
#define CHI2LIBCUDAQHULL

#include <string>
#include <sstream>
#include <algorithm>
#include <math.h>
#include "../../Utils/MyLogger.h"
#include "../../Utils/FileUtils.h"
#include "Container/cuMyPeak.h"

using namespace std;

class Chi2LibCudaQhull {
private:
	/**
	 * Elimina los espacios al inicio y al final del string
	 */
	static void trim(string& str);

	/**
	 * Recorta es string segun el delimitador y el/los resultados los adjunta al vector de strings
	 */
	static void stringSplit(string str, string delim, vector<string> *out);

	/**
	 * Prepara los datos de cuMyPeakArray como string para ingresarlos a Qhull
	 */
	static string prepareData(cuMyPeakArray *peaks);

	/**
	 * Interpreta los datos de Qhull segun la ejecucion "qhull v Qbb p FN" y los almacena el el vector de vertices y de celdas
	 */
	static void interpretData(string *data, vector< pair<double,double> > *vertex, vector< vector<int> > *cell);
public:
	/**
	 * Ejecuta qhull con los datos ingresados en el string "data" y segun los parametros especificados en el string "params"
	 */
	static string execQhull(string data, string params);

	/**
	 * Agrega las areas de voronoi respectivas a cada uno de los cuMyPeaks dentro del arreglo.
	 */
	static void addVoronoiAreas(cuMyPeakArray *peaks);
};

#endif
