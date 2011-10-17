/*
 * Chi2LibMatrix.h
 *
 *  Created on: 02/10/2011
 *      Author: juanin
 */
#include "../../Container/MyMatrix.h"
#include "../../Utils/MyLogger.h"

#ifndef CHI2LIBMATRIX
#define CHI2LIBMATRIX

class Chi2LibMatrix {
public:
	/**
	 * Eleva al cuadrado la matriz
	 */
	static void squareIt(MyMatrix<double> *mtrx);
	/**
	 * Eleva al cubo la matriz
	 */
	static void cubeIt(MyMatrix<double> *mtrx);
	/**
	 * Rellena la matrix con el numero indicado
	 */
	static void fillWith(MyMatrix<double> *mtrx, double fill);
	/**
	 * Rellena la matrix con el numero indicado
	 */
	static void fillWith(MyMatrix<int> *mtrx, int fill);
	/**
	 * Copia una matriz a la otra matriz
	 */
	static void copy(MyMatrix<double> *in, MyMatrix<double> *out);
	static void copy(MyMatrix<int> *in, MyMatrix<int> *out);
};

#endif
