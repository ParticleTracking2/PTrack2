/*
 * Image.h
 *
 *  Created on: 11-06-2011
 *      Author: juanin
 */
#include "PNGImageReader.h"

string PNGImageReader::name(){
	return "PNG";
}
PNGImageReader::PNGImageReader(){
	cout << ">> Constructing " << name() << endl;
}

PNGImageReader::~PNGImageReader(){
	cout << ">> Destructing " << name() << endl;
}

Image *PNGImageReader::decodeImage(){
	cout << ">> Decoding " << name() << endl;
	return new Image();
}
