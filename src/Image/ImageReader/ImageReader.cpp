/*
 * ImageReader
 *
 *  Created on: 11-06-2011
 *      Author: juanin
 */

#include "ImageReader.h"

MyImage ImageReader::decodeImageGray(string file){
	MyLogger::log()->debug("[ImageReader] Decoding Generic Image...");
	MyLogger::log()->debug("[ImageReader] Returning 0x0 Image");
	return MyImage(0,0);
}
