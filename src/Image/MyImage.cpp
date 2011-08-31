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
void MyImage::getHiLo(){
	double hi = this->getValue(0,0);
	double lo = this->getValue(0,0);
	for(unsigned int x = 0; x < this->getWidth(); ++x)
		for(unsigned int y = 0; y < this->getHeight(); ++y){
			if(hi < this->getValue(x,y))
				hi = this->getValue(x,y);
			if(lo > this->getValue(x,y))
				lo = this->getValue(x,y);
		}

	this->_hi = hi;
	this->_lo = lo;
}

void MyImage::normalize(){
	double newval;
	double dif = _hi-_lo;
	for(unsigned int x =0; x < getWidth(); ++x)
		for(unsigned int y =0; y < getHeight(); ++y){
			newval = (_hi-getValue(x,y)*1.0)/dif;
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

void MyImage::printHiLo(){
	cout << "High: " << _hi << "; Low: " << _lo << endl;
}
