/*
 * ImageFactory.h
 *
 *  Created on: 12-06-2011
 *      Author: juanin
 */
#include "MyImage.h"

#ifndef MYIMAGEFACTORY
#define MYIMAGEFACTORY

class MyImageFactory {
public:
	enum MyImageTypes{
		IMAGE_JPG=0,
		IMAGE_PNG=1,
		IMAGE_TIF=2
	};
	static MyImage *makeImgFromFile(string file);
};

#endif
