/*
 * PNGImageReader.h
 *
 *  Created on: 12-06-2011
 *      Author: juanin
 */
#include "ImageReader.h"

#ifndef PNGIMAGEREADER
#define PNGIMAGEREADER

class PNGImageReader : public ImageReader {
public:
	static MyImage decodeImageGray(string file);
};


#endif
