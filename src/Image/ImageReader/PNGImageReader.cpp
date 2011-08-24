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

MyImage *PNGImageReader::decodeImage(string file){
	cout << ">> Decoding " << name() << endl;
	return new MyImage();
}
