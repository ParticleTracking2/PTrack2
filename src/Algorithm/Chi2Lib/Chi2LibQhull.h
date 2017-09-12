/*
 * Chi2LibQhull.h
 *
 *  Created on: 08/10/2011
 *      Author: juanin
 */

#ifndef CHI2LIBQHULL
#define CHI2LIBQHULL

#include <unistd.h>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <math.h>
#include "../../Utils/MyLogger.h"
#include "../../Utils/FileUtils.h"
#include "../MyPeak.h"

using namespace std;

/**
 * Clase para ejecuar Qhull y obtener datos a partir de los datos recibidos.
 */
class Chi2LibQhull {
private:

	/**
	 * Separa un string segun un delimitador y almacena estos string separados dentro del vector de strings.
	 * @param str String a separar
	 * @param delim String delimitador.
	 * @param out Vector de String en el cual almacenar los strings separados.
	 */
	static void stringSplit(string str, string delim, vector<string> *out);

	/**
	 * Prepara los datos para ser entregados a Qhull como string.
	 * @param peaks Vector de peaks a ser entregados a qhull.
	 * @return String de datos representando al vector de peaks en formato aceptable para qhull.
	 */
	static string prepareData(vector<MyPeak> *peaks);

	/**
	 * Interpreta los datos recibidos de Qhull segun la opcion "qhull v Qbb p FN".
	 * Almacena los datos de Vertices y celdas entregados por qhull.
	 * @param data Datos de salida en bruto de qhull.
	 * @param vertex Vector de pares representando vertices en donde almacenar los vertices obtenidos a traves de qhull.
	 * @param cell Vector de vectores de enteros en donde almacenar las celdas que entrega qhull.
	 */
	static void interpretData(string *data, vector< pair<double,double> > *vertex, vector< vector<int> > *cell);
public:

	/**
	 * Ejecuta Qhull entregandole los datos de data como texto plano segun los parametros de params.
	 * La salida de datos se encuentra en bruto como texto plano.
	 * @param data Datos en texto plano para entregar a Qhull y ejecutar.
	 * @param params Parametros de ejecucion de Qhull.
	 */
	static string execQhull(string data, string params);

	/**
	 * Agrega las areas de Voronoi generadas a traves de la ejecucion de Qhull a los peaks.
	 * @param peaks Vector de peaks encontrados a los cuales se le agregaran las areas de voronoi respectivas.
	 */
	static void addVoronoiAreas(vector<MyPeak> *peaks);

    /**
     * parsea un string " num1   num2 "  y captura los dos floats.
     */
    static void parse_pair(const char *str, float *a, float *b);
};

#endif
