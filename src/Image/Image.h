/*
 * Image.h
 *
 *  Created on: 11-06-2011
 *      Author: juanin
 */
#include <string>
#include <stdlib.h>

using namespace std;

#ifndef IMAGE
#define IMAGE

class Image {
private:
	unsigned int width;
	unsigned int height;
	unsigned char ** pixels;

	void allocPixels();
	void freePixels();
public:
	static string name();
	Image();
	Image(unsigned int width, unsigned int height);
	virtual ~Image();

	void setWidth(unsigned int width);
	void setHeight(unsigned int height);
	void reset(unsigned char def = 0);
};

#endif
