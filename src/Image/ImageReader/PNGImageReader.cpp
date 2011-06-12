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

PNGImageReader::~PNGImageReader(){
	// TODO Auto-generated destructor stub
	cout << ">> Destructing " << name() << endl;
}

Image *PNGImageReader::decodeImage(){
	// TODO Auto-generated stub
	cout << ">> Decoding " << name() << endl;
	return new Image();
}
