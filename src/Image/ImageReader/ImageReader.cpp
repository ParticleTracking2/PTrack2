/*
 * ImageReader
 *
 *  Created on: 11-06-2011
 *      Author: juanin
 */

#include "ImageReader.h"

MyImage ImageReader::decodeImageGray(string file){
	MyLogger::log()->debug("[ImageReader] Decoding Generic Image: %s", file.c_str());
	Magick::Image my_image;
	my_image.read(file);
	my_image.rotate(90);

	unsigned int max_x = my_image.columns();
	unsigned int max_y = my_image.rows();

	MyImage ret(max_x, max_y);
	Magick::ColorGray my_color;
	for(unsigned int x = 0; x < max_x; ++x)
		for(unsigned int y = 0; y < max_y; ++y){
			my_color = my_image.pixelColor(x,y);
			ret(x,y) = my_color.shade();
		}

	MyLogger::log()->debug("[ImageReader] Generic Image Decoded");
	return ret;
}

MyImage ImageReader::decodeImageGray(string file, unsigned int cut){
	MyLogger::log()->debug("[ImageReader] Decoding Generic Image: %s; Cut=%i", file.c_str(), cut);
	Magick::Image my_image;
	my_image.read(file);
	my_image.crop( Magick::Geometry(my_image.columns()-2*cut, my_image.rows()-2*cut, cut, cut, false, false));
	my_image.rotate(90);

	unsigned int max_x = my_image.columns();
	unsigned int max_y = my_image.rows();

	MyImage ret(max_x, max_y);
	Magick::ColorGray my_color;
	for(unsigned int x = 0; x < max_x; ++x)
		for(unsigned int y = 0; y < max_y; ++y){
			my_color = my_image.pixelColor(x,y);
			ret(x,y) = my_color.shade();
		}

	MyLogger::log()->debug("[ImageReader] Generic Image Decoded");
	return ret;
}

MyImage ImageReader::decodeImageGray(string file, unsigned int top, unsigned int bottom, unsigned int left, unsigned int right){
	MyLogger::log()->debug("[ImageReader] Decoding Generic Image: %s", file.c_str());
	Magick::Image my_image;
	my_image.read(file);
	my_image.crop( Magick::Geometry(my_image.columns()-left-right, my_image.rows()-top-bottom, left, top, false, false));
	my_image.rotate(90);

	unsigned int max_x = my_image.columns();
	unsigned int max_y = my_image.rows();

	MyImage ret(max_x, max_y);
	Magick::ColorGray my_color;
	for(unsigned int x = 0; x < max_x; ++x)
		for(unsigned int y = 0; y < max_y; ++y){
			my_color = my_image.pixelColor(x,y);
			ret(x,y) = my_color.shade();
		}

	MyLogger::log()->debug("[ImageReader] Generic Image Decoded");
	return ret;
}
