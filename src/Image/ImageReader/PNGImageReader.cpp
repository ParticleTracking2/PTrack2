/*
 * Image.h
 *
 *  Created on: 11-06-2011
 *      Author: juanin
 */
#include "PNGImageReader.h"

string PNGImageReader::name(){
	return "PNG";
}

/**
 *******************************
 * Constructores y Destructores
 *******************************
 */
PNGImageReader::PNGImageReader(){
	// Do Nothing
}

PNGImageReader::~PNGImageReader(){
	// Do Nothing
}

/**
 *******************************
 * Metodos
 *******************************
 */
MyImage *PNGImageReader::decodeImage(string file){
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

	return ret;
}
