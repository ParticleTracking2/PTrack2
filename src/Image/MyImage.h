/*
 * Image.h
 *
 *  Created on: 11-06-2011
 *      Author: juanin
 */
#include "../Algorithm/MyPeak.h"
#include "../Container/MyMatrix.h"
#include "../Utils/MyLogger.h"
#include <vector>
#include <stdlib.h>
#include <Magick++.h>

#ifndef MYIMAGE
#define MYIMAGE

class MyImage {
private:
	MyMatrix<double> mtrx;
public:
	MyImage() { }
	~MyImage() { }
	MyImage(unsigned int width, unsigned int height);

	double & operator ()(int x, int y);
	MyMatrix<double>* matrix();
	void display();
	void display(vector<MyPeak> *peaks);
};

#endif
