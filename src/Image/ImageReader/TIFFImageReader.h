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
	struct TiffPartition{
		int x1, x2, y1, y2;
		MyImage *img;
		Magick::Image *mimg;
	};
	static void *populate(void *ptr);
public:
	static MyImage decodeImageGray(string file);
	static MyImage decodeImageGray(string file, unsigned int cut);
	static MyImage decodeImageGray(string file, unsigned int top, unsigned int bottom, unsigned int left, unsigned int right);
};

#endif
