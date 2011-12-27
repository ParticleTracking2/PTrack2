/*
 * ImageFactory.h
 *
 *  Created on: 12-06-2011
 *      Author: juanin
 */
#include "MyImage.h"
#include "ImageReader/ImageReader.h"
#include "ImageReader/JPGImageReader.h"
#include "ImageReader/PNGImageReader.h"
#include "ImageReader/TIFFImageReader.h"
#include "../Utils/MyLogger.h"
#include <string>

#ifndef MYIMAGEFACTORY
#define MYIMAGEFACTORY

using namespace std;

/**
 * Tipos de imagenes soportadas actualmente.
 */
enum MyImageTypes{
	IMAGE_JPG=0,
	IMAGE_PNG=1,
	IMAGE_TIF=2
};

class MyImageFactory {
private:
	/**
	 * Reconoce el tipo de imagen en base a su extension.
	 */
	static MyImageTypes recognizeType(string file);
public:
	/**
	 * Crea un objeto MyImage a partir de la ruta y nombre de la imagen.
	 */
	static MyImage makeImgFromFile(string file);

	/**
	 * Crea un objeto MyImage a partir de la ruta y nombre de la imagen.
	 * Además recorta la imagen en todos sus bordes segun cut.
	 */
	static MyImage makeImgFromFile(string file, unsigned int cut);
};

#endif
