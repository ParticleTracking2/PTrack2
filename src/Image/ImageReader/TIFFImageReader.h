/*
 * TIFFImageReader.h
 *
 *  Created on: 12-06-2011
 *      Author: juanin
 */
#include "ImageReader.h"
#include <Magick++.h>

#ifndef TIFFIMAGEREADER
#define TIFFIMAGEREADER

class TIFFImageReader : public ImageReader {
public:
	static string name();

	TIFFImageReader();
	virtual ~TIFFImageReader();

	MyImage *decodeImage(string file);
};

#endif
