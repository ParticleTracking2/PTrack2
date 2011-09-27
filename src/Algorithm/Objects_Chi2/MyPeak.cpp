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

MyPeak::MyPeak(double x, double y){
	setX(x);
	setY(y);
}

MyPeak::MyPeak(double x, double y, double intensity){
	setX(x);
	setY(y);
	setIntensity(intensity);
}
/**
 *******************************
 * Metodos
 *******************************
 */

void MyPeak::setX(double x){
	_x = x;
}
void MyPeak::setY(double y){
	_y = y;
}
void MyPeak::setIntensity(double intensity){
	_intensity = intensity;
}

double MyPeak::getX(){
	return _x;
}

double MyPeak::getY(){
	return _y;
}

double MyPeak::getIntensity(){
	return _intensity;
}
