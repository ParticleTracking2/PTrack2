/*
 * Image.h
 *
 *  Created on: 11-06-2011
 *      Author: juanin
 */
#include <stdlib.h>
#include <iostream>
#include <Magick++.h>

using namespace std;

#ifndef MYIMAGE
#define MYIMAGE

class MyImage {
private:
	unsigned int width;
	unsigned int height;
	unsigned char ** pixels;

	void allocPixels();
	void freePixels();
public:
	MyImage();
	MyImage(unsigned int width, unsigned int height);
	virtual ~MyImage();

	void setWidth(unsigned int width);
	void setHeight(unsigned int height);
	unsigned int getWidth();
	unsigned int getHeight();
	void setPixel(unsigned int x, unsigned int y, unsigned char color);
	unsigned char getPixel(unsigned int x, unsigned int y);
	void display();
	void reset(unsigned char def = 0);
};

#endif
