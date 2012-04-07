/*
 * Image.h
 *
 *  Created on: 11-06-2011
 *      Author: juanin
 */

#ifdef CHI2CUDA
#include "Container/cuMyMatrix.h"
#endif
#include "../Algorithm/MyPeak.h"
#include "../Container/MyMatrix.h"
#include "../Utils/MyLogger.h"
#include <vector>
#include <string>
#include <stdlib.h>
#include <Magick++.h>

#ifndef MYIMAGE
#define MYIMAGE

/**
 * Clase para representar una imagen como una matriz de dos dimensiones de doubles.
 * La imagen representada se puede interpretar teoricamente como una imagen a escala de grises.
 */
class MyImage {
private:

	/**
	 * Contenedor de datos.
	 */
	MyMatrix<double> mtrx;

	/**
	 * Imagen temporal a desplegar.
	 */
	Magick::Image my_image;

	/**
	 * Establece si ya se generó una imagen con peaks.
	 */
	bool is_generated;
public:

	/**
	 * Constructor Vacio.
	 */
	MyImage();

	/**
	 * Destructor
	 */
	~MyImage();

	/**
	 * Constructor en base a dos dimensiones. Ancho y alto.
	 * @param width Ancho de la imagen a representar
	 * @param height Alto de la imagen a representar
	 */
	MyImage(unsigned int width, unsigned int height);

	/**
	 * Constructor a base de una matriz de dos dimensiones de double.
	 * @param trx Matriz de datos representativos de la imagen.
	 */
	MyImage(MyMatrix<double> *trx);

#ifdef CHI2CUDA
	/**
	 * Constructor a base de una matriz de dos dimensiones de double.
	 * @param trx Matriz de datos representativos de la imagen.
	 */
	MyImage(cuMyMatrix *trx);
#endif

	/**
	 * Operador () que devuelve el contenido de la posicion X e Y de la imagen.
	 * @param x Posicion en X
	 * @param y Posicion en Y
	 * @return Valor de la imagen en la posicion X e Y
	 */
	double & operator ()(unsigned int x, unsigned int y);

	/**
	 * Operador = para copiar una imagen
	 * @param img Imagen a copiar
	 */
	void operator = (MyImage img);

	/**
	 * Devuelve la matriz representante de la imagen.
	 * @return Matriz representante
	 */
	MyMatrix<double>* matrix();

	/**
	 * Despliega en pantalla la imagen representada.
	 */
	void display();

	/**
	 * Genera y Despliega en pantalla la imagen representada. Además agrega puntos representados por el vector de MyPeak,
	 * los cuales pueden ser solidos o liquidos y el color de estos es azul o rojo respectivamente.
	 * Los puntos son representados como circulos centrados en el peak con un diametro igual al entregado.
	 * @param peaks Vector de MyPeak a desplegar en la imagen.
	 * @param diameter Diametro de las particulas a desplegar, si no se entrega, el valor por defecto es 4.
	 */
	void display(vector<MyPeak> *peaks, double diameter = 4);

	/**
	 * Genera la imagen procesada con los peaks encontrados los cuales pueden ser solidos o liquidos y el color de estos es azul o rojo respectivamente.
	 * Los puntos son representados como circulos centrados en el peak con un diametro igual al entregado.
	 * @param peaks Vector de MyPeak a desplegar en la imagen.
	 * @param diameter Diametro de las particulas a desplegar, si no se entrega, el valor por defecto es 4.
	 */
	void generateDisplayable(vector<MyPeak> *peaks, double diameter = 4);

	/**
	 * Genera y Guarda la imagen procesada con los peaks encontradosos cuales pueden ser solidos o liquidos y el color de estos es azul o rojo respectivamente.
	 * Los puntos son representados como circulos centrados en el peak con un diametro igual al entregado.
	 * @param path String de la ubicacion a donde guardar la imagen.
	 * @param peaks Vector de MyPeak a desplegar en la imagen.
	 * @param diameter Diametro de las particulas a desplegar, si no se entrega, el valor por defecto es 4.
	 */
	void saveDisplayableToDisk(string path, vector<MyPeak> *peaks,  double diameter = 4);
};

#endif
