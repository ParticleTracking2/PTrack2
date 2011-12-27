/*
 * Image.h
 *	Clase para representar una imagen como una matriz de dos dimensiones de doubles.
 *  Created on: 11-06-2011
 *      Author: juanin
 */
#include "../Algorithm/MyPeak.h"
#include "../Container/MyMatrix.h"
#include "../Utils/MyLogger.h"
#include <vector>
#include <stdlib.h>
#include <Magick++.h>

#ifndef MYIMAGE
#define MYIMAGE

class MyImage {
private:
	/**
	 * Contenedor de datos.
	 */
	MyMatrix<double> mtrx;
public:
	/**
	 * Constructor Vacio.
	 */
	MyImage() { }

	/**
	 * Destructor
	 */
	~MyImage();

	/**
	 * Constructor en base a dos dimensiones. Ancho y alto.
	 */
	MyImage(unsigned int width, unsigned int height);

	/**
	 * Constructor a base de una matriz de dos dimensiones de double.
	 */
	MyImage(MyMatrix<double> *trx);

	/**
	 * Operador () que devuelve el contenido de la posicion X e Y de la imagen.
	 */
	double & operator ()(int x, int y);

	/**
	 * Operador = para copiar una imagen
	 */
	void operator = (MyImage img);

	/**
	 * Devuelve la matriz representante de la imagen.
	 */
	MyMatrix<double>* matrix();

	/**
	 * Despliega en pantalla la imagen contenida en esta instancia.
	 */
	void display();

	/**
	 * Despliega en pantalla la imagen contenida en esta instancia y además
	 * agrega puntos representados por el vector de MyPeak.
	 */
	void display(vector<MyPeak> *peaks);
};

#endif
