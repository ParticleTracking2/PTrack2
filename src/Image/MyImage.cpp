/*
 * Image.h
 *
 *  Created on: 11-06-2011
 *      Author: juanin
 */

#include "MyImage.h"

/**
 *******************************
 * Metodos
 *******************************
 */

void MyImage::normalize(){
	double newval;
	double dif = this->getHigh()-this->getLow();
	for(unsigned int x =0; x < getWidth(); ++x)
		for(unsigned int y =0; y < getHeight(); ++y){
			newval = (this->getHigh()-getValue(x,y)*1.0)/dif;
			setValue(x,y,newval);
		}
}

void MyImage::display(){
	Magick::Image my_image(Magick::Geometry(this->getWidth(), this->getHeight()), Magick::ColorGray(0));
	Magick::ColorGray my_color;
	for(unsigned int x = 0; x < this->getWidth(); ++x)
			for(unsigned int y = 0; y < this->getHeight(); ++y){
				my_color.shade(this->getValue(x,y));
				my_image.pixelColor(x,y, my_color);
			}
	my_image.display();
}
