/*
 * PNGImageReader.h
 *
 *  Created on: 12-06-2011
 *      Author: juanin
 */
#include "../Image.h"
#include "ImageReader.h"
#include <iostream>

#ifndef PNGIMAGEREADER
#define PNGIMAGEREADER

using namespace std;

class PNGImageReader : public ImageReader {
private:
	static string name();
public:
	virtual ~PNGImageReader();

	Image *decodeImage();
};


#endif
