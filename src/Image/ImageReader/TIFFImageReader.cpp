/*
 * Image.h
 *
 *  Created on: 11-06-2011
 *      Author: juanin
 */
#include "TIFFImageReader.h"

/**
 *******************************
 * Metodos
 *******************************
 */
MyImage TIFFImageReader::decodeImageGray(string file){
	MyLogger::log()->debug("[TIFFImageReader] Decoding TIFF Image: %s", file.c_str());
	Magick::Image my_image;
	my_image.read(file);
	my_image.colorSpace(Magick::GRAYColorspace);

	unsigned int max_x = my_image.rows();
	unsigned int max_y = my_image.columns();

	MyImage ret(max_x, max_y);
	Magick::ColorGray my_color;
	for(unsigned int x = 0; x < max_x; ++x)
		for(unsigned int y = 0; y < max_y; ++y){
			my_color = my_image.pixelColor(x,y);
			ret(max_y-y-1,x) = my_color.shade();
		}

	MyLogger::log()->debug("[TIFFImageReader] TIFF Image Decoded");
	return ret;
}
