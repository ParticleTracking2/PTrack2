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

/**
 * Clase para manejar Matrices del tipo MyMatrix.
 */
class Chi2LibMatrix {
public:
	/**
	 * Eleva al cuadrado la matriz entregada como parametro.
	 * @param mtrx Matriz a elevar al cuadrado.
	 */
	static void squareIt(MyMatrix<double> *mtrx);

	/**
	 * Eleva al cubo la matriz entregada como parametro.
	 * @param mtrx Matriz a elevar al cubo.
	 */
	static void cubeIt(MyMatrix<double> *mtrx);

	/**
	 * Copia una matriz a otra matriz.
	 * @param in Matriz origen de datos.
	 * @param out Matriz salida de datos.
	 */
	static void copy(MyMatrix<double> *in, MyMatrix<double> *out);

	/**
	 * Copia una matriz a otra matriz.
	 * @param in Matriz origen de datos.
	 * @param out Matriz salida de datos.
	 */
	static void copy(MyMatrix<int> *in, MyMatrix<int> *out);
};

#endif
