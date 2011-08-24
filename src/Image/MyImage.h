/*
 * Image.h
 *
 *  Created on: 11-06-2011
 *      Author: juanin
 */
#include <string>
#include <stdlib.h>

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
	static string name();
	MyImage();
	MyImage(unsigned int width, unsigned int height);
	virtual ~MyImage();

	void setWidth(unsigned int width);
	void setHeight(unsigned int height);
	void reset(unsigned char def = 0);
};

#endif
