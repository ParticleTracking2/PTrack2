/*
 * Image.h
 *
 *  Created on: 11-06-2011
 *      Author: juanin
 */
#include "TIFFImageReader.h"

string TIFFImageReader::name(){
	return "TIFF";
}
/**
 *******************************
 * Constructores y Destructores
 *******************************
 */
TIFFImageReader::TIFFImageReader(){
	// Do Nothing
}

TIFFImageReader::~TIFFImageReader(){
	// Do Nothing
}

/**
 *******************************
 * Metodos
 *******************************
 */
MyImage *TIFFImageReader::decodeImage(string file){
	cout << ">> Decoding " << name() << endl;

	Magick::Image my_image;
	my_image.read(file);

	unsigned int max_x = my_image.columns();
	unsigned int max_y = my_image.rows();

	MyImage *ret = new MyImage(max_x, max_y);
	Magick::ColorGray my_color;
	unsigned char my_color_mean;
	for(unsigned int x = 0; x < max_x; ++x)
		for(unsigned int y = 0; y < max_y; ++y){
			my_color = my_image.pixelColor(x,y);
			my_color_mean = (unsigned char)(my_color.shade()*255);
			ret->setPixel(x,y,my_color_mean);
		}

// Crear Nueva imagen de ImageMagick a partir de la clase Propia y desplegar.
//	Magick::Image my_image2(Magick::Geometry(max_x, max_y), Magick::ColorGray(0));
//	for(unsigned int x = 0; x < max_x; ++x)
//			for(unsigned int y = 0; y < max_y; ++y){
//				my_color.shade(ret->getPixel(x,y)/255.0);
//				my_image2.pixelColor(x,y, my_color);
//			}
//	my_image2.display();

	return ret;
}
