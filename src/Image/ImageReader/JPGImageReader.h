/*
 * JPGImageReader.h
 *
 *  Created on: 12-06-2011
 *      Author: juanin
 */
#include "../Image.h"
#include "ImageReader.h"
#include <iostream>

#ifndef JPGIMAGEREADER
#define JPGIMAGEREADER

using namespace std;

class JPGImageReader : public ImageReader {
private:
	static string name();
public:
	virtual ~JPGImageReader();
	Image *decodeImage();
};

#endif
