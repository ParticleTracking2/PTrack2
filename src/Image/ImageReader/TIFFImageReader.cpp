/*
 * Image.h
 *
 *  Created on: 11-06-2011
 *      Author: juanin
 */
#include "TIFFImageReader.h"

string TIFFImageReader::name(){
	return "TIFF";
}

TIFFImageReader::TIFFImageReader(){
	cout << ">> Constructing " << name() << endl;
}

TIFFImageReader::~TIFFImageReader(){
	// TODO Auto-generated destructor stub
	cout << ">> Destructing " << name() << endl;
}

Image *TIFFImageReader::decodeImage(){
	// TODO Auto-generated stub
	cout << ">> Decoding " << name() << endl;
	return new Image();
}
