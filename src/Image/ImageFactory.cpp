/*
 * ImageFactory.cpp
 *
 *  Created on: 11-06-2011
 *      Author: juanin
 */
#include "MyImage.h"
#include "ImageFactory.h"
#include "ImageReader/ImageReader.h"
#include "ImageReader/JPGImageReader.h"
#include "ImageReader/PNGImageReader.h"
#include "ImageReader/TIFFImageReader.h"

ImageFactory::ImageFactory(){
	// Do nothing
}

ImageFactory::~ImageFactory(){
	// Do nothing
}
/**
 * Construye una imagen manipulable a partir de la ruta de una imagen de disco
 */
MyImage *ImageFactory::makeImgFromFile(string file){
	MyImage *ret;
	ImageReader *reader;

	string typetxt = file.substr(file.find_last_of(".")+1, file.length());
	ImageTypes type;
	if(!typetxt.compare("tif") || !typetxt.compare("TIF") || !typetxt.compare("tiff") || !typetxt.compare("TIFF"))
		type = IMAGE_TIF;
	if(!typetxt.compare("jpg") || !typetxt.compare("JPG") || !typetxt.compare("jpeg") || !typetxt.compare("JPEG"))
		type = IMAGE_JPG;
	if(!typetxt.compare("png") || !typetxt.compare("PNG"))
		type = IMAGE_PNG;

	switch(type){
		case IMAGE_JPG :
			reader = new JPGImageReader();
			ret = reader->decodeImage(file);
			break;
		case IMAGE_PNG:
			reader = new PNGImageReader();
			ret = reader->decodeImage(file);
			break;
		case IMAGE_TIF:
			reader = new TIFFImageReader();
			ret = reader->decodeImage(file);
			break;
	}
	delete reader;
	return ret;
}

ImageFactory* ImageFactory::myInstance = 0;

ImageFactory* ImageFactory::getInstance(){
	if(!myInstance)
		myInstance = new ImageFactory();
	return myInstance;
}
