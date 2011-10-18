/*
 * TIFFImageReader.h
 *
 *  Created on: 12-06-2011
 *      Author: juanin
 */
#include "ImageReader.h"
#include "pthread.h"

#ifndef TIFFIMAGEREADER
#define TIFFIMAGEREADER

class TIFFImageReader : public ImageReader {
private:
	struct Partition{
		unsigned int x1, x2, y1, y2;
		MyImage *img;
		Magick::Image *mimg;
	};
	static void *populate(void *ptr);
public:
	static MyImage decodeImageGray(string file);
};

#endif
