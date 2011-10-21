/*
 * ImageReader.h
 *
 *  Created on: 12-06-2011
 *      Author: juanin
 */
#include "../MyImage.h"
#include "../../Utils/MyLogger.h"
#include <Magick++.h>
#include <iostream>
using namespace std;

#ifndef IMAGEREADER
#define IMAGEREADER

class ImageReader {
public:
	virtual ~ImageReader();
	static MyImage decodeImageGray(string file);
	static MyImage decodeImageGray(string file, unsigned int cut);
	static MyImage decodeImageGray(string file, unsigned int top, unsigned int bottom, unsigned int left, unsigned int right);
};

#endif
