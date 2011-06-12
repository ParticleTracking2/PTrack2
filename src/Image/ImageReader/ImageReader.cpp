/*
 * ImageReader
 *
 *  Created on: 11-06-2011
 *      Author: juanin
 */

#include "ImageReader.h"
#include <iostream>
using namespace std;

ImageReader::ImageReader(){
	// TODO Auto-generated constructor stub
	cout << ">> Constructing " << "Generic" << endl;
}
ImageReader::~ImageReader(){

}

Image *ImageReader::decodeImage(){
	cout << ">> Decoding " << "Generic" << endl;
	return new Image();
}
