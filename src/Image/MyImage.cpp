/*
 * Image.h
 *
 *  Created on: 11-06-2011
 *      Author: juanin
 */

#include "MyImage.h"

/**
 *******************************
 * Constructores
 *******************************
 */

MyImage::MyImage(unsigned int width, unsigned int height){
	MyLogger::log()->debugStream() << "[MyImage] Alocating Image: Size = " << width << "x" << height;
	mtrx.allocate(width, height);
	MyLogger::log()->debug("[MyImage] Image Alocated");
}

MyImage::~MyImage(){
	mtrx.deallocate();
}

void MyImage::operator = (MyImage img){
	mtrx.allocate(img.matrix()->sX(), img.matrix()->sY());
	for(unsigned int x=0; x < img.matrix()->sX(); ++x)
		for(unsigned int y=0; y < img.matrix()->sY(); ++y){
			mtrx.at(x,y) = img.matrix()->getValue(x,y);
		}
}

/**
 *******************************
 * Metodos
 *******************************
 */
void MyImage::display(){
	MyLogger::log()->debug("[MyImage] Displaying Image: Size = %ix%i",mtrx.sX(), mtrx.sY());
	Magick::Image my_image(Magick::Geometry(mtrx.sX(), mtrx.sY()), Magick::ColorGray(0));
	Magick::ColorGray my_color;
	for(unsigned int x = 0; x < mtrx.sX(); ++x){
		for(unsigned int y = 0; y < mtrx.sY(); ++y){
			my_color.shade(mtrx.at(x,y));
			my_image.pixelColor(x,y, my_color);
		}
	}

	my_image.display();
	MyLogger::log()->debug("[MyImage] Image Displayed");
}

void MyImage::display(vector<MyPeak> *peaks){
	MyLogger::log()->debug("[MyImage] Displaying Image: Size = %ix%i; Peaks=%i",mtrx.sX(), mtrx.sY(), peaks->size());
	Magick::Image my_image(Magick::Geometry(mtrx.sX(), mtrx.sY()), Magick::ColorRGB(0,0,0));
	Magick::ColorRGB my_color;
	for(unsigned int x = 0; x < mtrx.sX(); ++x){
		for(unsigned int y = 0; y < mtrx.sY(); ++y){
			my_color.blue(mtrx.at(x,y));
			my_color.red(mtrx.at(x,y));
			my_color.green(mtrx.at(x,y));
			my_image.pixelColor(x,y, my_color);
		}
	}

	Magick::ColorRGB dotR(1.0, 0.0, 0.0);
	Magick::ColorRGB dotB(0.0, 0.0, 1.0);
	int diameter = 1;
	for(unsigned int i=0; i< peaks->size(); ++i){
		if(	0 <= peaks->at(i).px && (unsigned int)peaks->at(i).px < mtrx.sX() && 0 <= peaks->at(i).py && (unsigned int)peaks->at(i).py < mtrx.sY()){
			for(int subx = -diameter; subx <= diameter; ++subx){
				for(int suby = -diameter; suby <= diameter; ++suby){
					ssize_t sx = (ssize_t)(mtrx.sY()-(peaks->at(i).py+subx));
					ssize_t sy = (ssize_t)(peaks->at(i).px+suby);
					if(	0 <= sx && (unsigned int)sx < mtrx.sX() && 0 <= sy && (unsigned int)sy < mtrx.sY()){
						if(peaks->at(i).solid)
							my_image.pixelColor(sx, sy, dotR);
						else
							my_image.pixelColor(sx, sy, dotB);
					}
				}
			}
		}else{
			MyLogger::log()->debug("[MyImage] Peak Excluded: X=%f; Y=%f",peaks->at(i).px, peaks->at(i).py );
		}
	}

	my_image.display();
	MyLogger::log()->debug("[MyImage] Image Displayed");
}

double & MyImage::operator ()(int x, int y){
	return mtrx.at(x,y);
}

MyMatrix<double>* MyImage::matrix(){
	return &mtrx;
}
