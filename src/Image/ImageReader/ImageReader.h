/*
 * ImageReader.h
 *
 *  Created on: 12-06-2011
 *      Author: juanin
 */
#include "../MyImage.h"
#include <Magick++.h>
#include <iostream>
using namespace std;

#ifndef IMAGEREADER
#define IMAGEREADER

class ImageReader {
public:
	virtual ~ImageReader() { };
	virtual MyImage *decodeImage(string image);
};

#endif
