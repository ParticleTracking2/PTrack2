/*
 * Image.h
 *
 *  Created on: 11-06-2011
 *      Author: juanin
 */

#include "Image.h"

string Image::name(){
	return "Image";
}

/**
 *******************************
 * Constructores y Destructores
 *******************************
 */
Image::Image() {
	// Hagase nada!
}

Image::Image(unsigned int width, unsigned int height){
	this->setHeight(height);
	this->setWidth(width);
	this->reset();
}

Image::~Image() {
	if(this->pixels)
		this->freePixels();
}

void Image::allocPixels(){
	this->pixels = (unsigned char **)malloc((this->height)*sizeof(unsigned char *));
	for(unsigned int i=0; i< this->height; ++i){
		this->pixels[i] = (unsigned char *)malloc((this->width)*sizeof(unsigned char *));
	}
}
void Image::freePixels(){
	for(unsigned int i=0; i< this->height; ++i){
		free(this->pixels[i]);
	}
	free(this->pixels);
}
/**
 *******************************
 * Metodos
 *******************************
 */
void Image::setWidth(unsigned int width){
	this->width = width;
}

void Image::setHeight(unsigned int height){
	this->height = height;
}

void Image::reset(unsigned char def){
	if(!this->pixels)
		this->allocPixels();

	for(unsigned int y=0; y<this->height; ++y){
		for(unsigned int x=0; x<this->width; ++x){
			this->pixels[y][x]= def;
		}
	}
}
