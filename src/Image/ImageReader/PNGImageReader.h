/*
 * PNGImageReader.h
 *
 *  Created on: 12-06-2011
 *      Author: juanin
 */
#include "../ImageReader.h"

#ifndef PNGIMAGEREADER
#define PNGIMAGEREADER

/**
 * Clase para leer archivos de imagenes PNG.
 * Delega la decodificacion a ImageReader
 */
class PNGImageReader : public ImageReader {
public:
	/**
	 * Constructor Vacio
	 */
	PNGImageReader();

	/**
	 * Destructor Vacio
	 */
	~PNGImageReader();
};


#endif
