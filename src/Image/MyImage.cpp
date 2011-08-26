/*
 * Image.h
 *
 *  Created on: 11-06-2011
 *      Author: juanin
 */

#include "MyImage.h"

/**
 *******************************
 * Constructores y Destructores
 *******************************
 */
MyImage::MyImage() {
	// Hagase nada!
}

MyImage::MyImage(unsigned int width, unsigned int height){
	this->pixels = 0;
	setHeight(height);
	setWidth(width);
	reset();
}

MyImage::~MyImage() {
	this->pixels = 0;
	if(pixels)
		freePixels();
}

void MyImage::allocPixels(){
	pixels = (unsigned char **)malloc((width)*sizeof(unsigned char *));
	for(unsigned int i=0; i<width; ++i){
		pixels[i] = (unsigned char *)malloc((height)*sizeof(unsigned char *));
	}
}
void MyImage::freePixels(){
	for(unsigned int i=0; i<width; ++i){
		free(pixels[i]);
	}
	free(pixels);
}
/**
 *******************************
 * Metodos
 *******************************
 */
void MyImage::setWidth(unsigned int width){
	this->width = width;
}

void MyImage::setHeight(unsigned int height){
	this->height = height;
}

void MyImage::setPixel(unsigned int x, unsigned int y, unsigned char color){
	if(x < this->width && y < this->height)
		pixels[x][y] = color;
}

unsigned int MyImage::getWidth(){
	return this->width;
}

unsigned int MyImage::getHeight(){
	return this->height;
}

unsigned char MyImage::getPixel(unsigned int x, unsigned int y){
	if(x < this->width && y < this->height)
		return pixels[x][y];
	return 0;
}

void MyImage::display(){
	Magick::Image my_image(Magick::Geometry(this->width, this->height), Magick::ColorGray(0));
	Magick::ColorGray my_color;
	for(unsigned int x = 0; x < this->width; ++x)
			for(unsigned int y = 0; y < this->height; ++y){
				my_color.shade(this->pixels[x][y]/255.0);
				my_image.pixelColor(x,y, my_color);
			}
	my_image.display();
}

void MyImage::reset(unsigned char def){
	if(!pixels)
		allocPixels();

	for(unsigned int x=0; x<width; ++x){
		for(unsigned int y=0; y<height; ++y){
			pixels[x][y]= def;
		}
	}
}
