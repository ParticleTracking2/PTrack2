/*
 * ImageReader.h
 *
 *  Created on: 12-06-2011
 *      Author: juanin
 */
#include "../Image.h"

#ifndef IMAGEREADER
#define IMAGEREADER

class ImageReader {
public:
	ImageReader();
	virtual ~ImageReader();

	virtual Image *decodeImage();
};

#endif
