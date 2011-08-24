/*
 * ImageFactory.h
 *
 *  Created on: 12-06-2011
 *      Author: juanin
 */
#include "MyImage.h"
#include <string>
using namespace std;

#ifndef IMAGEFACTORY
#define IMAGEFACTORY

enum ImageTypes{
	IMAGE_JPG=0,
	IMAGE_PNG=1,
	IMAGE_TIF=2
};

class ImageFactory {
private:
	static ImageFactory *myInstance;
	ImageFactory();
	virtual ~ImageFactory();

public:
	static string name();
	MyImage *makeImgFromFile(string file);
	static ImageFactory *getInstance();
};

#endif
