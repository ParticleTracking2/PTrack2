/*
 * FILEUTILS.h
 *	Clase con Utilidades varias para hacer Debug en archivos de distintos tipos de datos.
 *  Created on: 02/10/2011
 *      Author: ptrack
 */
#include "../Container/MyMatrix.h"
#include "../Algorithm/MyPeak.h"
#include "MyLogger.h"
#include "Container/cuMyMatrix.h"

#include <fftw3.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#ifndef FILEUTILS
#define FILEUTILS

using namespace std;

class FileUtils {
public:
	static void writeToFile(string str, const char* file);
	static void writeToFileM(vector< pair<double,double> > *vertex, vector< vector<int> > *cell, const char* file);

	static void writeToFileM(double *arr, MyMatrix<double> *ref, int nwidth, const char* file);

	static void writeToFileM(cuMyMatrix *arr, const char* file);
	static void writeToFileM(cuMyMatrixi *arr, const char* file);
	static void writeToFileM(fftw_complex *arr, unsigned int size, const char* file);
	static void writeToFileM(double *arr, unsigned int width, unsigned int height, const char* file);

	static void writeToFileM(MyMatrix<double> *arr, const char* file);
	static void writeToFileM(MyMatrix<int> *arr, const char* file);
	static void writeToFileM(vector<MyPeak> *peaks, const char* file);
	static void writeToFileMA(vector<MyPeak> *peaks, const char* file);
	static void writeToFileM(vector<double> *vec, const char* file);

	static void writeToFile(MyMatrix<double> *arr, const char* file);
	static void writeToFile(MyMatrix<int> *arr, const char* file);
	static void writeToFile(vector<MyPeak> *peaks, const char* file);
	static void writeToFile(vector<double> *vec, const char* file);
};

#endif /* MYUTILS */
