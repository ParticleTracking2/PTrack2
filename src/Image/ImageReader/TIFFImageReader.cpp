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

MyImage *TIFFImageReader::decodeImage(string file){
	// TODO Auto-generated stub
	cout << ">> Decoding " << name() << endl;

	Magick::Image my_image;
	my_image.read(file);
	my_image.display();

	return new MyImage();
}
