/*
 * ImageFactory.h
 *
 *  Created on: 12-06-2011
 *      Author: juanin
 */
#include "MyImage.h"
#include "ImageReader/ImageReader.h"
#include "ImageReader/JPGImageReader.h"
#include "ImageReader/PNGImageReader.h"
#include "ImageReader/TIFFImageReader.h"
#include "../Utils/MyLogger.h"
#include <string>

#ifndef MYIMAGEFACTORY
#define MYIMAGEFACTORY

using namespace std;

enum MyImageTypes{
	IMAGE_JPG=0,
	IMAGE_PNG=1,
	IMAGE_TIF=2
};

class MyImageFactory {
private:
	static MyImageTypes recognizeType(string file);
public:
	static MyImage makeImgFromFile(string file);
};

#endif
