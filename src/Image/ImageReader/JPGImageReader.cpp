/*
 * Image.h
 *
 *  Created on: 11-06-2011
 *      Author: juanin
 */
#include "JPGImageReader.h"

string JPGImageReader::name(){
	return "JPG";
}

JPGImageReader::~JPGImageReader(){
	cout << ">> Destructing " << name() << endl;
}

Image *JPGImageReader::decodeImage(){
	// TODO Auto-generated stub
	cout << ">> Decoding " << name() << endl;
	return new Image();
}
