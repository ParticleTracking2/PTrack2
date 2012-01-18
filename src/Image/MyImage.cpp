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

MyImage::MyImage(MyMatrix<double> *trx){
	mtrx.allocate(trx->sX(), trx->sY());
	for(unsigned int x=0; x < mtrx.sX(); ++x)
		for(unsigned int y=0; y < mtrx.sY(); ++y){
			mtrx.at(x,y) = trx->getValue(x,y);
		}
}

#ifdef CHI2CUDA
MyImage::MyImage(cuMyMatrix *trx){
	trx->copyToHost();
	mtrx.allocate(trx->sizeX(), trx->sizeY());
	for(unsigned int x=0; x < mtrx.sX(); ++x)
		for(unsigned int y=0; y < mtrx.sY(); ++y){
			mtrx.at(x,y) = trx->getValueHost(x,y);
		}
}
#endif

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
	my_image.negate(true);

	Magick::ColorRGB dotF(0.0, 0.0, 0.0);
	dotF.alpha(1.0);
	my_image.fillColor(dotF);

	Magick::ColorRGB dotR(1.0, 0.0, 0.0);
	dotR.alpha(0.25);
	Magick::ColorRGB dotB(0.0, 0.0, 1.0);
	dotB.alpha(0.25);
	for(unsigned int i=0; i< peaks->size(); ++i){
		unsigned int px = (unsigned int)peaks->at(i).px;
		unsigned int py = (unsigned int)peaks->at(i).py;
		if(	px < mtrx.sX() && py < mtrx.sY()){
			if(peaks->at(i).solid)
				my_image.strokeColor(dotR);
			else
				my_image.strokeColor(dotB);
			my_image.draw(Magick::DrawableCircle(peaks->at(i).px, peaks->at(i).py, peaks->at(i).px+2.5, peaks->at(i).py+2.5));
		}else{
			MyLogger::log()->debug("[MyImage] Peak Excluded: X=%f; Y=%f",peaks->at(i).px, peaks->at(i).py );
		}
	}

	my_image.display();
	MyLogger::log()->debug("[MyImage] Image Displayed");
	my_image.write("tmp.png");
}

double & MyImage::operator ()(unsigned int x, unsigned int y){
	return mtrx.at(x,y);
}

MyMatrix<double>* MyImage::matrix(){
	return &mtrx;
}
