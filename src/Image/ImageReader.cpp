/*
 * ImageReader
 *
 *  Created on: 11-06-2011
 *      Author: juanin
 */

#include "ImageReader.h"
/**
 *******************************
 * Constructores
 *******************************
 */
ImageReader::ImageReader() { }

ImageReader::~ImageReader() { }

/**
 *******************************
 * Metodos
 *******************************
 */
MyImage ImageReader::decodeImageGray(string file){
	MyLogger::log()->debug("[ImageReader] Decoding Generic Image: %s", file.c_str());
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

	MyLogger::log()->debug("[ImageReader] Generic Image Decoded");
	return ret;
}

MyMatrix<double> ImageReader::decodeRawGray(string file){
	MyLogger::log()->debug("[ImageReader] Decoding Generic Image: %s", file.c_str());
	Magick::Image my_image;
	my_image.read(file);

	unsigned int max_x = my_image.columns();
	unsigned int max_y = my_image.rows();

	MyMatrix<double> ret(max_x, max_y);
	Magick::ColorGray my_color;
	for(unsigned int x = 0; x < max_x; ++x)
		for(unsigned int y = 0; y < max_y; ++y){
			my_color = my_image.pixelColor(x,y);
			ret(x,y) = my_color.shade();
		}

	MyLogger::log()->debug("[ImageReader] Generic Image Decoded");
	return ret;
}

#ifdef CHI2CUDA
cuMyMatrix ImageReader::decodeCuRawGray(string file){
	MyLogger::log()->debug("[ImageReader] Decoding Generic Image: %s", file.c_str());
	Magick::Image my_image;
	my_image.read(file);

	unsigned int max_x = my_image.columns();
	unsigned int max_y = my_image.rows();

	cuMyMatrix ret(max_x, max_y);
	ret.copyToHost();
	Magick::ColorGray my_color;
	for(unsigned int x = 0; x < max_x; ++x)
		for(unsigned int y = 0; y < max_y; ++y){
			my_color = my_image.pixelColor(x,y);
			ret.atHost(x,y) = (float)my_color.shade();
		}

	ret.copyToDevice();
	ret.deallocateHost();

	MyLogger::log()->debug("[ImageReader] Generic Image Decoded");
	return ret;
}
#endif

MyImage ImageReader::decodeImageGray(string file, unsigned int cut){
	MyLogger::log()->debug("[ImageReader] Decoding Generic Image: %s; Cut=%i", file.c_str(), cut);
	Magick::Image my_image;
	my_image.read(file);
	my_image.crop( Magick::Geometry(my_image.columns()-2*cut, my_image.rows()-2*cut, cut, cut, false, false));

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

MyMatrix<double> ImageReader::decodeRawGray(string file, unsigned int cut){
	MyLogger::log()->debug("[ImageReader] Decoding Generic Image: %s", file.c_str());
	Magick::Image my_image;
	my_image.read(file);
	my_image.crop( Magick::Geometry(my_image.columns()-2*cut, my_image.rows()-2*cut, cut, cut, false, false));

	unsigned int max_x = my_image.columns();
	unsigned int max_y = my_image.rows();

	MyMatrix<double> ret(max_x, max_y);
	Magick::ColorGray my_color;
	for(unsigned int x = 0; x < max_x; ++x)
		for(unsigned int y = 0; y < max_y; ++y){
			my_color = my_image.pixelColor(x,y);
			ret(x,y) = my_color.shade();
		}

	MyLogger::log()->debug("[ImageReader] Generic Image Decoded");
	return ret;
}

#ifdef CHI2CUDA
cuMyMatrix ImageReader::decodeCuRawGray(string file, unsigned int cut){
	MyLogger::log()->debug("[ImageReader] Decoding Generic Image: %s", file.c_str());
	Magick::Image my_image;
	my_image.read(file);
	my_image.crop( Magick::Geometry(my_image.columns()-2*cut, my_image.rows()-2*cut, cut, cut, false, false));

	unsigned int max_x = my_image.columns();
	unsigned int max_y = my_image.rows();

	cuMyMatrix ret(max_x, max_y);
	ret.copyToHost();
	Magick::ColorGray my_color;
	for(unsigned int x = 0; x < max_x; ++x)
		for(unsigned int y = 0; y < max_y; ++y){
			my_color = my_image.pixelColor(x,y);
			ret.atHost(x,y) = (float)my_color.shade();
		}
	ret.copyToDevice();
	ret.deallocateHost();

	MyLogger::log()->debug("[ImageReader] Generic Image Decoded");
	return ret;
}
#endif
