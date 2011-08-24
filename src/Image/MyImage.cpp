/*
 * Image.h
 *
 *  Created on: 11-06-2011
 *      Author: juanin
 */

#include "MyImage.h"

string MyImage::name(){
	return "Image";
}

/**
 *******************************
 * Constructores y Destructores
 *******************************
 */
MyImage::MyImage() {
	// Hagase nada!
}

MyImage::MyImage(unsigned int width, unsigned int height){
	this->setHeight(height);
	this->setWidth(width);
	this->reset();
}

MyImage::~MyImage() {
	if(this->pixels)
		this->freePixels();
}

void MyImage::allocPixels(){
	this->pixels = (unsigned char **)malloc((this->height)*sizeof(unsigned char *));
	for(unsigned int i=0; i< this->height; ++i){
		this->pixels[i] = (unsigned char *)malloc((this->width)*sizeof(unsigned char *));
	}
}
void MyImage::freePixels(){
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
void MyImage::setWidth(unsigned int width){
	this->width = width;
}

void MyImage::setHeight(unsigned int height){
	this->height = height;
}

void MyImage::reset(unsigned char def){
	if(!this->pixels)
		this->allocPixels();

	for(unsigned int y=0; y<this->height; ++y){
		for(unsigned int x=0; x<this->width; ++x){
			this->pixels[y][x]= def;
		}
	}
}
