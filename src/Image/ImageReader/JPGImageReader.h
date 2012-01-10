/*
 * JPGImageReader.h
 *
 *  Created on: 12-06-2011
 *      Author: juanin
 */
#include "../ImageReader.h"

#ifndef JPGIMAGEREADER
#define JPGIMAGEREADER

/**
 * Clase para leer archivos de imagenes JPG.
 * Delega la decodificacion a ImageReader
 */
class JPGImageReader : public ImageReader {
public:
	/**
	 * Constructor Vacio
	 */
	JPGImageReader();

	/**
	 * Destructor Vacio
	 */
	~JPGImageReader();
};

#endif
