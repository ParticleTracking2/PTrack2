/*
 * ImageReader
 *
 *  Created on: 11-06-2011
 *      Author: juanin
 */

#include "ImageReader.h"

string ImageReader::name(){
	return "Generic ImageReader";
}

Image *ImageReader::decodeImage(){
	cout << ">> Decoding " << name() << endl;
	return new Image();
}
