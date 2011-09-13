/*
 * MyPeak.cpp
 *
 *  Created on: 12/09/2011
 *      Author: juanin
 */

#include "MyPeak.h"

/**
 *******************************
 * Constructores y Destructores
 *******************************
 */

MyPeak::MyPeak(){
	_x = 0;
	_y = 0;
	_intensity = 0;
}

MyPeak::MyPeak(unsigned int x, unsigned int y){
	setX(x);
	setY(y);
}

MyPeak::MyPeak(unsigned int x, unsigned int y, double intensity){
	setX(x);
	setY(y);
	setIntensity(intensity);
}
/**
 *******************************
 * Metodos
 *******************************
 */

void MyPeak::setX(unsigned int x){
	_x = x;
}
void MyPeak::setY(unsigned int y){
	_y = y;
}
void MyPeak::setIntensity(double intensity){
	_intensity = intensity;
}

unsigned int MyPeak::getX(){
	return _x;
}

unsigned int MyPeak::getY(){
	return _y;
}

double MyPeak::getIntensity(){
	return _intensity;
}
