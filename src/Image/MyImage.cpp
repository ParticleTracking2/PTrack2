/*
 * Image.h
 *
 *  Created on: 11-06-2011
 *      Author: juanin
 */

#include "MyImage.h"

/**
 *******************************
 * Constructores
 *******************************
 */

MyImage::MyImage(unsigned int width, unsigned int height){
	MyLogger::log()->debugStream() << "[MyImage] Alocating Image: Size = " << width << "x" << height;
	mtrx.allocate(width, height);
	MyLogger::log()->debug("[MyImage] Image Alocated");
}

/**
 *******************************
 * Metodos
 *******************************
 */
void MyImage::display(){
	MyLogger::log()->debug("[MyImage] Displaying Image: Size = %fx%f",mtrx.sX(), mtrx.sY());
	Magick::Image my_image(Magick::Geometry(mtrx.sX(), mtrx.sY()), Magick::ColorGray(0));
	Magick::ColorGray my_color;
	for(unsigned int x = 0; x < mtrx.sX(); ++x){
		for(unsigned int y = 0; y < mtrx.sY(); ++y){
			my_color.shade(mtrx.at(x,y));
			my_image.pixelColor(x,y, my_color);
		}
	}

	my_image.display();
	MyLogger::log()->debug("[MyImage] Image Displayed");
}

double & MyImage::operator ()(int x, int y){
	return mtrx.at(x,y);
}

MyMatrix<double>* MyImage::matrix(){
	return &mtrx;
}
