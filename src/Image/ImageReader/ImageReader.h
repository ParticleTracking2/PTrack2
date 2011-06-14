/*
 * ImageReader.h
 *
 *  Created on: 12-06-2011
 *      Author: juanin
 */
#include "../Image.h"
#include <iostream>
#include <string>
using namespace std;

#ifndef IMAGEREADER
#define IMAGEREADER

class ImageReader {
public:
	static string name();
	virtual Image *decodeImage();
};

#endif
