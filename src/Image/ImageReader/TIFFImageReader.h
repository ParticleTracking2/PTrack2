/*
 * TIFFImageReader.h
 *
 *  Created on: 12-06-2011
 *      Author: juanin
 */
#include "../ImageReader.h"
#include "pthread.h"

#ifndef TIFFIMAGEREADER
#define TIFFIMAGEREADER

/**
 * Clase para leer archivos de imagenes TIF.
 * Reimplementa los metodos de ImageReader para ser leidos por 2 threads.
 */
class TIFFImageReader : public ImageReader {
private:

#ifdef CHI2CUDA
	/**
	 * Estructura de particion para generar la imagen.
	 */
	struct TiffPartition{
		int x1, x2, y1, y2;
		MyMatrix<double> *img;
		cuMyMatrix *cuimg;
		Magick::Image *mimg;
	};

	/**
	 * Puebla los datos de la imagen. ptr debe ser un puntero a la estructura TiffPartition.
	 */
	static void *populate(void *ptr);

	/**
	 * Puebla los datos de la imagen. ptr debe ser un puntero a la estructura TiffPartition.
	 */
	static void *populateCu(void *ptr);
#endif
public:
	/**
	 * Constructor Vacio
	 */
	TIFFImageReader();

	/**
	 * Destructor Vacio
	 */
	~TIFFImageReader();

#ifdef CHI2CUDA
	/**
	 * Decodifica una Imagen a escala de grises.
	 * @param file Ruta completa de la imagen.
	 * @return Imagen decodificada y almacenada como MyMatrix<double>.
	 */
	MyMatrix<double> decodeRawGray(string file);

	/**
	 * Decodifica una Imagen a escala de grises.
	 * @param file Ruta completa de la imagen.
	 * @return Imagen decodificada y almacenada como cuMyMatrix.
	 */
	cuMyMatrix decodeCuRawGray(string file);
#endif
};

#endif
