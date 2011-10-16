/*
 * TIFFImageReader.h
 *
 *  Created on: 12-06-2011
 *      Author: juanin
 */
#include "ImageReader.h"

#ifndef TIFFIMAGEREADER
#define TIFFIMAGEREADER

class TIFFImageReader : public ImageReader {
public:
	static MyImage decodeImageGray(string file);
};

#endif
