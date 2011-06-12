/*
 * ImageFactory.h
 *
 *  Created on: 12-06-2011
 *      Author: juanin
 */
#include "Image.h"

#ifndef IMAGEFACTORY
#define IMAGEFACTORY

enum ImageTypes{
	JPG=0,
	PNG=1,
	TIFF=2
};

class ImageFactory {

private:
	static ImageFactory *myInstance;

protected:
	ImageFactory();

	virtual ~ImageFactory();

public:
	Image *makeImgFromFile(ImageTypes file);

	static ImageFactory *getInstance();
};

#endif
