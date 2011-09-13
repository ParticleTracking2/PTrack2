/*
 * Image.h
 *
 *  Created on: 11-06-2011
 *      Author: juanin
 */
#include "../Container/Array2D.h"
#include <stdlib.h>
#include <iostream>
#include <Magick++.h>

using namespace std;

#ifndef MYIMAGE
#define MYIMAGE

class MyImage : public Array2D<double>{
public:
	MyImage(): Array2D() {}
	MyImage(unsigned int width, unsigned int height): Array2D(width, height) { this->getHiLo(); }
	MyImage(Array2D<double>* data): Array2D(data) { this->getHiLo(); }
	void normalize();
	void display();
};

#endif
