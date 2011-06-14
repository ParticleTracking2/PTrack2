/*
 * ImageFactory.cpp
 *
 *  Created on: 11-06-2011
 *      Author: juanin
 */
#include "Image.h"
#include "ImageFactory.h"
#include "ImageReader/ImageReader.h"
#include "ImageReader/JPGImageReader.h"
#include "ImageReader/PNGImageReader.h"
#include "ImageReader/TIFFImageReader.h"

ImageFactory::ImageFactory(){

}

ImageFactory::~ImageFactory(){

}

Image *ImageFactory::makeImgFromFile(ImageTypes type){
		Image *ret;
		ImageReader *reader;

		switch(type){
			case IMAGE_JPG :
				reader = new JPGImageReader();
				ret = reader->decodeImage();
				break;
			case IMAGE_PNG:
				reader = new PNGImageReader();
				ret = reader->decodeImage();
				break;
			case IMAGE_TIFF:
				reader = new TIFFImageReader();
				ret = reader->decodeImage();
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
