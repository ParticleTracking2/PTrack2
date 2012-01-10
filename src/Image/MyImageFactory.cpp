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
	ImageReader *reader;
	MyImage ret;
	MyImageTypes type = recognizeType(file);
	switch(type){
		case IMAGE_JPG :
			MyLogger::log()->debug("[MyImageFactory] JPG Image type detected");
			reader = new JPGImageReader();
			ret = reader->decodeImageGray(file);
			break;
		case IMAGE_PNG:
			MyLogger::log()->debug("[MyImageFactory] PNG Image type detected");
			reader = new PNGImageReader();
			ret = reader->decodeImageGray(file);
			break;
		case IMAGE_TIF:
			MyLogger::log()->debug("[MyImageFactory] TIFF Image type detected");
			reader = new TIFFImageReader();
			ret = reader->decodeImageGray(file);
			break;
		default:
			MyLogger::log()->debug("[MyImageFactory] TIFF Image type detected");
			reader = new ImageReader();
			ret = reader->decodeImageGray(file);
			break;
	}

	delete reader;
	return ret;
}

MyImage MyImageFactory::makeImgFromFile(string file, unsigned int cut){
	ImageReader *reader;
	MyImage ret;
	MyImageTypes type = recognizeType(file);
	switch(type){
		case IMAGE_JPG :
			MyLogger::log()->debug("[MyImageFactory] JPG Image type detected");
			reader = new JPGImageReader();
			ret = reader->decodeImageGray(file, cut);
			break;
		case IMAGE_PNG:
			MyLogger::log()->debug("[MyImageFactory] PNG Image type detected");
			reader = new PNGImageReader();
			ret = reader->decodeImageGray(file, cut);
			break;
		case IMAGE_TIF:
			MyLogger::log()->debug("[MyImageFactory] TIFF Image type detected");
			reader = new TIFFImageReader();
			ret = reader->decodeImageGray(file, cut);
			break;
		default:
			MyLogger::log()->debug("[MyImageFactory] TIFF Image type detected");
			reader = new ImageReader();
			ret = reader->decodeImageGray(file, cut);
			break;
	}

	delete reader;
	return ret;
}

MyMatrix<double> MyImageFactory::makeRawImgFromFile(string file){
	ImageReader *reader;
	MyMatrix<double> ret;
	MyImageTypes type = recognizeType(file);
	switch(type){
		case IMAGE_JPG :
			MyLogger::log()->debug("[MyImageFactory] JPG Image type detected");
			reader = new JPGImageReader();
			ret = reader->decodeRawGray(file);
			break;
		case IMAGE_PNG:
			MyLogger::log()->debug("[MyImageFactory] PNG Image type detected");
			reader = new PNGImageReader();
			ret = reader->decodeRawGray(file);
			break;
		case IMAGE_TIF:
			MyLogger::log()->debug("[MyImageFactory] TIFF Image type detected");
			reader = new TIFFImageReader();
			ret = reader->decodeRawGray(file);
			break;
		default:
			MyLogger::log()->debug("[MyImageFactory] TIFF Image type detected");
			reader = new ImageReader();
			ret = reader->decodeRawGray(file);
			break;
	}

	delete reader;
	return ret;
}

MyMatrix<double> MyImageFactory::makeRawImgFromFile(string file, unsigned int cut){
	ImageReader *reader;
	MyMatrix<double> ret;
	MyImageTypes type = recognizeType(file);
	switch(type){
		case IMAGE_JPG :
			MyLogger::log()->debug("[MyImageFactory] JPG Image type detected");
			reader = new JPGImageReader();
			ret = reader->decodeRawGray(file, cut);
			break;
		case IMAGE_PNG:
			MyLogger::log()->debug("[MyImageFactory] PNG Image type detected");
			reader = new PNGImageReader();
			ret = reader->decodeRawGray(file, cut);
			break;
		case IMAGE_TIF:
			MyLogger::log()->debug("[MyImageFactory] TIFF Image type detected");
			reader = new TIFFImageReader();
			ret = reader->decodeRawGray(file, cut);
			break;
		default:
			MyLogger::log()->debug("[MyImageFactory] TIFF Image type detected");
			reader = new ImageReader();
			ret = reader->decodeRawGray(file, cut);
			break;
	}

	delete reader;
	return ret;
}

cuMyMatrix MyImageFactory::makeCuRawImgFromFile(string file){
	ImageReader *reader;
	cuMyMatrix ret;
	MyImageTypes type = recognizeType(file);
	switch(type){
		case IMAGE_JPG :
			MyLogger::log()->debug("[MyImageFactory] JPG Image type detected");
			reader = new JPGImageReader();
			ret = reader->decodeCuRawGray(file);
			break;
		case IMAGE_PNG:
			MyLogger::log()->debug("[MyImageFactory] PNG Image type detected");
			reader = new PNGImageReader();
			ret = reader->decodeCuRawGray(file);
			break;
		case IMAGE_TIF:
			MyLogger::log()->debug("[MyImageFactory] TIFF Image type detected");
			reader = new TIFFImageReader();
			ret = reader->decodeCuRawGray(file);
			break;
		default:
			MyLogger::log()->debug("[MyImageFactory] TIFF Image type detected");
			reader = new ImageReader();
			ret = reader->decodeCuRawGray(file);
			break;
	}

	delete reader;
	return ret;
}

cuMyMatrix MyImageFactory::makeCuRawImgFromFile(string file, unsigned int cut){
	ImageReader *reader;
	cuMyMatrix ret;
	MyImageTypes type = recognizeType(file);
	switch(type){
		case IMAGE_JPG :
			MyLogger::log()->debug("[MyImageFactory] JPG Image type detected");
			reader = new JPGImageReader();
			ret = reader->decodeCuRawGray(file, cut);
			break;
		case IMAGE_PNG:
			MyLogger::log()->debug("[MyImageFactory] PNG Image type detected");
			reader = new PNGImageReader();
			ret = reader->decodeCuRawGray(file, cut);
			break;
		case IMAGE_TIF:
			MyLogger::log()->debug("[MyImageFactory] TIFF Image type detected");
			reader = new TIFFImageReader();
			ret = reader->decodeCuRawGray(file, cut);
			break;
		default:
			MyLogger::log()->debug("[MyImageFactory] TIFF Image type detected");
			reader = new ImageReader();
			ret = reader->decodeCuRawGray(file, cut);
			break;
	}

	delete reader;
	return ret;
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
