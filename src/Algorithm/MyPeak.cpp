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
	x = 0; y = 0;
	px = 0; py = 0;
	intensity = 0;
	solid = false;
}

MyPeak::MyPeak(int x, int y){
	this->x = x; this->y = y;
	px = x; py = y;
	solid = false;
}

MyPeak::MyPeak(int x, int y, double intensity){
	this->x = x; this->y = y;
	px = x; py = y;
	this->intensity = intensity;
	solid = false;
}
