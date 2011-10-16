/*
 * ImageFactory.cpp
 *
 *  Created on: 11-06-2011
 *      Author: juanin
 */
#include "MyImageFactory.h"

/**
 * Construye una imagen manipulable a partir de la ruta de una imagen de disco
 */
MyImage MyImageFactory::makeImgFromFile(string file){
	MyImageTypes type = recognizeType(file);
	switch(type){
		case IMAGE_JPG :
			MyLogger::log()->debug("[MyImageFactory] JPG Image type detected");
			return JPGImageReader::decodeImageGray(file);
		case IMAGE_PNG:
			MyLogger::log()->debug("[MyImageFactory] PNG Image type detected");
			return PNGImageReader::decodeImageGray(file);
		case IMAGE_TIF:
			MyLogger::log()->debug("[MyImageFactory] TIFF Image type detected");
			return TIFFImageReader::decodeImageGray(file);
	}

	return MyImage();
}

MyImageTypes MyImageFactory::recognizeType(string file){
	MyLogger::log()->debug("[MyImageFactory] Finding Extension of image...");
	string typetxt = file.substr(file.find_last_of(".")+1, file.length());
	MyImageTypes type;
	if(!typetxt.compare("tif") || !typetxt.compare("TIF") || !typetxt.compare("tiff") || !typetxt.compare("TIFF"))
		type = IMAGE_TIF;
	if(!typetxt.compare("jpg") || !typetxt.compare("JPG") || !typetxt.compare("jpeg") || !typetxt.compare("JPEG"))
		type = IMAGE_JPG;
	if(!typetxt.compare("png") || !typetxt.compare("PNG"))
		type = IMAGE_PNG;

	return type;
}
