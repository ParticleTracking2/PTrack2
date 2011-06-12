/*
 * TIFFImageReader.h
 *
 *  Created on: 12-06-2011
 *      Author: juanin
 */
#include "../Image.h"
#include "ImageReader.h"
#include <iostream>

#ifndef TIFFIMAGEREADER
#define TIFFIMAGEREADER

using namespace std;
class TIFFImageReader : public ImageReader {
private:
	static string name();
public:
	virtual ~TIFFImageReader();

	Image *decodeImage();
};

#endif
