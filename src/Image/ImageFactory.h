/*
 * ImageFactory.h
 *
 *  Created on: 12-06-2011
 *      Author: juanin
 */
#include "Image.h"
#include <string>
using namespace std;

#ifndef IMAGEFACTORY
#define IMAGEFACTORY

enum ImageTypes{
	IMAGE_JPG=0,
	IMAGE_PNG=1,
	IMAGE_TIFF=2
};

class ImageFactory {
private:
	static ImageFactory *myInstance;
	ImageFactory();
	virtual ~ImageFactory();

public:
	static string name();
	Image *makeImgFromFile(ImageTypes file);
	static ImageFactory *getInstance();
};

#endif
