/*
 * ImageReader.h
 *
 *  Created on: 12-06-2011
 *      Author: juanin
 */
#include "MyImage.h"
#include "../Utils/MyLogger.h"
#include <Magick++.h>
#include <iostream>
using namespace std;

#ifndef IMAGEREADER
#define IMAGEREADER

/**
 * Clase para implementar la lectura de archivos de imagenes.
 * Por defecto la clase lee archivos con ImageMagick por lo que debe soportar tantos formatos como ImageMagick pueda,
 * de lo contrario es necesario re implementar todos los metodos
 */
class ImageReader {
public:

	/**
	 * Destructor Virtual
	 */
	virtual ~ImageReader();

	/**
	 * Decodifica una Imagen a escala de grises.
	 * @param file Ruta completa de la imagen.
	 * @return Imagen decodificada y almacenada como MyImage.
	 */
	static MyImage decodeImageGray(string file);

	/**
	 * Decodifica una Imagen a escala de grises. Además recorta la imagen en todos sus bordes segun cut.
	 * @param file Ruta completa de la imagen.
	 * @param cut Tamaño del recorte de la imagen por todos los bordes.
	 * @return Imagen decodificada y almacenada como MyImage.
	 */
	static MyImage decodeImageGray(string file, unsigned int cut);
};

#endif
