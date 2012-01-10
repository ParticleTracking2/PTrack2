/*
 * ImageFactory.h
 *
 *  Created on: 12-06-2011
 *      Author: juanin
 */

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
	IMAGE_JPG=0,	/**< Tipo de imagen JPG */
	IMAGE_PNG=1,	/**< Tipo de imagen PNG */
	IMAGE_TIF=2		/**< Tipo de imagen TIF */
};

/**
 * Clase para construir imagenes en base a una direccion de un archivo de imagen.
 */
class MyImageFactory {
private:

	/**
	 * Reconoce el tipo de imagen en base a su extension.
	 * @param file ruta completa de una imagen.
	 * @return Tipo de archivo de imagen
	 */
	static MyImageTypes recognizeType(string file);
public:

	/**
	 * Crea un objeto MyImage a partir de la ruta y nombre de la imagen.
	 * @param file Ruta completa de una imagen.
	 * @return Imagen representada por la clase MyImage.
	 */
	static MyImage makeImgFromFile(string file);

	/**
	 * Crea un objeto MyImage a partir de la ruta y nombre de la imagen.
	 * @param file Ruta completa de una imagen.
	 * @return Imagen representada por la clase MyImage.
	 */
	static MyMatrix<double> makeRawImgFromFile(string file);

#ifdef CHI2CUDA
	/**
	 * Crea un objeto MyImage a partir de la ruta y nombre de la imagen.
	 * @param file Ruta completa de una imagen.
	 * @return Imagen representada por la clase MyImage.
	 */
	static cuMyMatrix makeCuRawImgFromFile(string file);
#endif

	/**
	 * Crea un objeto MyImage a partir de la ruta y nombre de la imagen.
	 * Además recorta la imagen en todos sus bordes segun cut.
	 * @param file Ruta completa de una imagen.
	 * @param cut Tamaño del recorte de la imagen por todos los bordes.
	 * @return Imagen representada por la clase MyImage.
	 */
	static MyImage makeImgFromFile(string file, unsigned int cut);

	/**
	 * Crea un objeto MyImage a partir de la ruta y nombre de la imagen.
	 * Además recorta la imagen en todos sus bordes segun cut.
	 * @param file Ruta completa de una imagen.
	 * @param cut Tamaño del recorte de la imagen por todos los bordes.
	 * @return Imagen representada por la clase MyImage.
	 */
	static MyMatrix<double> makeRawImgFromFile(string file, unsigned int cut);

#ifdef CHI2CUDA
	/**
	 * Crea un objeto MyImage a partir de la ruta y nombre de la imagen.
	 * Además recorta la imagen en todos sus bordes segun cut.
	 * @param file Ruta completa de una imagen.
	 * @param cut Tamaño del recorte de la imagen por todos los bordes.
	 * @return Imagen representada por la clase MyImage.
	 */
	static cuMyMatrix makeCuRawImgFromFile(string file, unsigned int cut);
#endif
};

#endif
