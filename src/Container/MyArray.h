/*
 * MyArray.h
 *
 *  Created on: 31/08/2011
 *      Author: juanin
 */
#include <cstdlib>

#ifndef MYARRAY
#define MYARRAY

template <class myType>
class MyArray{
private:
	unsigned int _width;
	unsigned int _height;
	myType** data;

	void allocateData();
	void freeData();
public:
	MyArray();
	MyArray(unsigned int width, unsigned int height);
	~MyArray();
	void setWidth(unsigned int width);
	void setHeight(unsigned int height);
	unsigned int getWidth();
	unsigned int getHeight();

	void setValue(unsigned int x, unsigned int y, myType val);
	myType getValue(unsigned int x, unsigned int y);

	void reset(myType def = 0);
};

/**
 *******************************
 * Constructores y Destructores
 *******************************
 */
template <class myType>
MyArray<myType>::MyArray() {
	this->data = 0;
}

template <class myType>
MyArray<myType>::MyArray(unsigned int width, unsigned int height){
	this->data = 0;
	setHeight(height);
	setWidth(width);
	reset();
}

template <class myType>
MyArray<myType>::~MyArray() {
	if(this->data)
		freeData();
}

template <class myType>
void MyArray<myType>::allocateData(){
	data = (myType **)malloc((_width)*sizeof(myType *));
		for(unsigned int i=0; i<_width; ++i){
			data[i] = (myType *)malloc((_height)*sizeof(myType));
		}
}

template <class myType>
void MyArray<myType>::freeData(){
	for(unsigned int i=0; i<_width; ++i){
		free(data[i]);
	}
	free(data);
}

/**
 *******************************
 * Metodos
 *******************************
 */
template <class myType>
void MyArray<myType>::setWidth(unsigned int width){
	this->_width = width;
}

template <class myType>
void MyArray<myType>::setHeight(unsigned int height){
	this->_height = height;
}

template <class myType>
unsigned int MyArray<myType>::getWidth(){
	return this->_width;
}

template <class myType>
unsigned int MyArray<myType>::getHeight(){
	return this->_height;
}

template <class myType>
void MyArray<myType>::setValue(unsigned int x, unsigned int y, myType val){
	if(x < _width && y < _height)
		data[x][y] = val;
}

template <class myType>
myType MyArray<myType>::getValue(unsigned int x, unsigned int y){
	if(x < _width && y < _height)
			return data[x][y];
	return 0;
}

template <class myType>
void MyArray<myType>::reset(myType def){
	if(!data)
		allocateData();

	for(unsigned int x=0; x<_width; ++x){
		for(unsigned int y=0; y<_height; ++y){
			data[x][y]= def;
		}
	}
}

#endif
