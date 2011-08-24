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

MyImage *ImageReader::decodeImage(string file){
	cout << ">> Decoding " << name() << endl;
	return new MyImage();
}
