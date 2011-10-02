/*
 * Array2D.h
 *
 *  Created on: 31/08/2011
 *      Author: juanin
 */
#include "math.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <cstdlib>

#ifndef ARRAY2D
#define ARRAY2D

using namespace std;

template <class myType>
class Array2D{
private:
	unsigned int _width;
	unsigned int _height;
	double _power;

	myType** data;
	myType _hi;
	myType _lo;

	void allocateData();
	void setWidth(unsigned int width);
	void setHeight(unsigned int height);
public:
	Array2D();
	Array2D(Array2D* arr2);
	Array2D(unsigned int width, unsigned int height);
	Array2D(unsigned int width, unsigned int height, myType def);
	~Array2D();
	unsigned int getWidth();
	unsigned int getHeight();
	myType getHigh();
	myType getLow();

	void setPower(double power);
	void setValue(unsigned int x, unsigned int y, myType val);
	void squareIt();
	void cubeIt();
	void normalize();

	myType getValue(unsigned int x, unsigned int y);
	myType getValuePow(unsigned int x, unsigned int y);

	void reset(myType def = 0);

	void getHiLo();
	void printInfo();
};

/**
 *******************************
 * Constructores y Destructores
 *******************************
 */
template <class myType>
Array2D<myType>::Array2D() {
	setPower(1);
	data = 0;
}

template <class myType>
Array2D<myType>::Array2D(Array2D* arr2){
	setPower(1);
	data = 0;
	setHeight(arr2->getWidth());
	setWidth(arr2->getHeight());
	reset();

	for(unsigned int x=0; x<_width; ++x)
		for(unsigned int y=0; y<_height; ++y){
			data[x][y] = arr2->getValue(x,y);
		}
}

template <class myType>
Array2D<myType>::Array2D(unsigned int width, unsigned int height){
	setPower(1);
	data = 0;
	setHeight(height);
	setWidth(width);
	reset();
}

template <class myType>
Array2D<myType>::Array2D(unsigned int width, unsigned int height, myType def){
	setPower(1);
	data = 0;
	setHeight(height);
	setWidth(width);
	reset(def);
}

template <class myType>
Array2D<myType>::~Array2D() {
	_width = 0;
	_height = 0;
	_power = 0;
	_hi = 0;
	_lo = 0;

	for(unsigned int h=0; h < _height; ++h){
		free(data[h]);
	}
	free(data);
}

template <class myType>
void Array2D<myType>::allocateData(){
	data = (myType**)malloc(_width*sizeof(myType));
	for(unsigned int h=0; h < _height; ++h){
		data[h] = (myType*)malloc(_height*sizeof(myType));
	}
}

/**
 *******************************
 * Metodos
 *******************************
 */
template <class myType>
void Array2D<myType>::setWidth(unsigned int width){
	this->_width = width;
}

template <class myType>
void Array2D<myType>::setHeight(unsigned int height){
	this->_height = height;
}

template <class myType>
unsigned int Array2D<myType>::getWidth(){
	return this->_width;
}

template <class myType>
unsigned int Array2D<myType>::getHeight(){
	return this->_height;
}

template <class myType>
myType Array2D<myType>::getHigh(){
	return this->_hi;
}

template <class myType>
myType Array2D<myType>::getLow(){
	return this->_lo;
}

template <class myType>
void Array2D<myType>::setValue(unsigned int x, unsigned int y, myType val){
	if(x < _width && y < _height)
		data[x][y] = val;
}

template <class myType>
void Array2D<myType>::setPower(double power){
	_power = power;
}

template <class myType>
void Array2D<myType>::squareIt(){
	for(unsigned int x=0; x<_width; ++x){
		for(unsigned int y=0; y<_height; ++y){
				data[x][y]= data[x][y]*data[x][y];
			}
		}
}

template <class myType>
void Array2D<myType>::cubeIt(){
	for(unsigned int x=0; x<_width; ++x){
		for(unsigned int y=0; y<_height; ++y){
				data[x][y]= data[x][y]*data[x][y]*data[x][y];
			}
		}
}

template <class myType>
void Array2D<myType>::normalize(){
	double newval;
	double dif = getHigh()-getLow();
	for(unsigned int x =0; x < getWidth(); ++x)
		for(unsigned int y =0; y < getHeight(); ++y){
			newval = (1.0*getHigh()-getValue(x,y)*1.0)/dif;
			setValue(x,y,newval);
		}
}

template <class myType>
myType Array2D<myType>::getValue(unsigned int x, unsigned int y){
	if(x < _width && y < _height){
		return data[x][y];
	}
	return 0;
}

template <class myType>
myType Array2D<myType>::getValuePow(unsigned int x, unsigned int y){
	if(x < _width && y < _height){
		return pow(data[x][y],_power);
	}
	return 0;
}

template <class myType>
void Array2D<myType>::reset(myType def){
	if(!data)
		allocateData();

	for(unsigned int x=0; x<_width; ++x){
		for(unsigned int y=0; y<_height; ++y){
			data[x][y]= def;
		}
	}
}

template <class myType>
void Array2D<myType>::getHiLo(){
	myType hi = getValue(0,0);
	myType lo = getValue(0,0);
	for(unsigned int x = 0; x < _width; ++x)
		for(unsigned int y = 0; y < _height; ++y){
			if(hi < getValue(x,y))
				hi = getValue(x,y);
			if(lo > getValue(x,y))
				lo = getValue(x,y);
		}

	this->_hi = hi;
	this->_lo = lo;
}

template <class myType>
void Array2D<myType>::printInfo(){
	getHiLo();
	cout << "Dimensions: " << this->getWidth() << " x " << this->getHeight() << endl;
	cout << "Values: Hi=" << _hi << "; Lo=" << _lo << endl;
}

#endif
