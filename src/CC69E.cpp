//============================================================================
// Name        : CC69E.cpp
// Author      : Juan Silva
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "Image/ImageFactory.h"
#include "Algorithm/Chi2Algorithm.h"

using namespace std;

int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	ImageFactory *_if = ImageFactory::getInstance();
	_if->makeImgFromFile(JPG);
	_if->makeImgFromFile(PNG);
	_if->makeImgFromFile(TIFF);

	void *pointer = new Chi2Algorithm();
	((Chi2Algorithm*)pointer)->run();

	return 0;
}
