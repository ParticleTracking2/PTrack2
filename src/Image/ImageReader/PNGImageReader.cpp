/*
 * Image.h
 *
 *  Created on: 11-06-2011
 *      Author: juanin
 */
#include "PNGImageReader.h"

/**
 *******************************
 * Metodos
 *******************************
 */
MyImage PNGImageReader::decodeImageGray(string file){
	MyLogger::log()->debug("[PNGImageReader] Decoding PNG Image: %s", file.c_str());
	Magick::Image my_image;
	my_image.read(file);

	unsigned int max_x = my_image.columns();
	unsigned int max_y = my_image.rows();

	MyImage ret(max_x, max_y);
	Magick::ColorGray my_color;
	for(unsigned int x = 0; x < max_x; ++x)
		for(unsigned int y = 0; y < max_y; ++y){
			my_color = my_image.pixelColor(x,y);
			ret(x,y) = my_color.shade();
		}

	MyLogger::log()->debug("[PNGImageReader] PNG Image Decoded");
	return ret;
}
