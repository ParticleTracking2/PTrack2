/*
 * ImageReader.h
 *
 *  Created on: 12-06-2011
 *      Author: juanin
 */
#include "../MyImage.h"
#include <iostream>
#include <string>
using namespace std;

#ifndef IMAGEREADER
#define IMAGEREADER

class ImageReader {
public:
	static string name();
	virtual ~ImageReader() { };
	virtual MyImage *decodeImage(string image);
};

#endif
