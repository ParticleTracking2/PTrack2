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

}

ImageFactory::~ImageFactory(){

}

MyImage *ImageFactory::makeImgFromFile(string file){
	MyImage *ret;
	ImageReader *reader;

	ImageTypes type = IMAGE_TIF;
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

string ImageFactory::name(){
	return "ImageFactory";
}

ImageFactory* ImageFactory::myInstance = 0;

ImageFactory* ImageFactory::getInstance(){
	if(!myInstance)
		myInstance = new ImageFactory();
	return myInstance;
}
