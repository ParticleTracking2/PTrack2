/*
 * Image.h
 *
 *  Created on: 11-06-2011
 *      Author: juanin
 */
#include <string>
using namespace std;

#ifndef IMAGE
#define IMAGE

class Image {
public:
	static string name();
	Image();

	virtual ~Image();
};

#endif
