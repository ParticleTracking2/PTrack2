/*
 * JPGImageReader.cpp
 *
 *  Created on: 11-06-2011
 *      Author: juanin
 */
#include "JPGImageReader.h"

string JPGImageReader::name(){
	return "JPG";
}

JPGImageReader::JPGImageReader(){
	cout << ">> Constructing " << name() << endl;
}

JPGImageReader::~JPGImageReader(){
	cout << ">> Destructing " << name() << endl;
}

MyImage *JPGImageReader::decodeImage(string file){
	cout << ">> Decoding " << name() << endl;
	return new MyImage();
}
