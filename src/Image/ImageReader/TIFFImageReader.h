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

	/**
	 * Estructura de particion para generar la imagen.
	 */
	struct TiffPartition{
		int x1, x2, y1, y2;
		MyImage *img;
		Magick::Image *mimg;
	};

	/**
	 * Puebla los datos de la imagen. ptr debe ser un puntero a la estructura TiffPartition.
	 */
	static void *populate(void *ptr);
public:

	/**
	 * Decodifica una Imagen TIFF a escala de grises. La decodificacion pasa en 2 Threads.
	 * @param file Ruta completa de la imagen.
	 * @return Imagen decodificada y almacenada como MyImage.
	 */
	static MyImage decodeImageGray(string file);

	/**
	 * Decodifica una Imagen a escala de grises. La decodificacion pasa en 2 Threads.
	 * Además recorta la imagen en todos sus bordes segun cut.
	 * @param file Ruta completa de la imagen.
	 * @param cut Tamaño del recorte de la imagen por todos los bordes.
	 * @return Imagen decodificada y almacenada como MyImage.
	 */
	static MyImage decodeImageGray(string file, unsigned int cut);
};

#endif
