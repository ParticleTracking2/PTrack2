/*
 * Matrix.h
 *
 *  Created on: 31/08/2011
 *      Author: juanin
 */
#include "../Utils/MyLogger.h"
#include <iostream>
#include <cstdlib>

#ifndef MYMATRIX
#define MYMATRIX

using namespace std;

template <class myType>
class MyMatrix{
private:
	myType** data;
	void allocate();
protected:
	unsigned int _sizeX;
	unsigned int _sizeY;
public:
	MyMatrix();
	MyMatrix(unsigned int x, unsigned int y);
	MyMatrix(unsigned int x, unsigned int y, myType def);
	~MyMatrix();

	unsigned int sX();
	unsigned int sY();
	void allocate(unsigned int x, unsigned int y);
	void deallocate();
	void reset(myType def = 0);

	myType getValue(unsigned int x, unsigned int y);
	myType & at(unsigned int x, unsigned int y);
	myType & operator () (unsigned int x, unsigned int y);
};

/**
 *******************************
 * Constructores y Destructores
 *******************************
 */
template <class myType>
MyMatrix<myType>::MyMatrix() {
	data = 0;
}

template <class myType>
MyMatrix<myType>::MyMatrix(unsigned int x, unsigned int y){
	data = 0;
	_sizeX = x; _sizeY = y;
	allocate();
}

template <class myType>
MyMatrix<myType>::MyMatrix(unsigned int x, unsigned int y, myType def){
	data = 0;
	_sizeX = x; _sizeY = y;
	allocate();
	reset(def);
}

template <class myType>
MyMatrix<myType>::~MyMatrix() {
	deallocate();
}

template <class myType>
void MyMatrix<myType>::allocate(){
	if(data)
		deallocate();

	MyLogger::log()->debug("[MyMatrix][allocate] Allocating %ix%i",_sizeX,_sizeY);
	data = new myType*[_sizeX];
	for(unsigned int h=0; h < _sizeX; ++h){
		data[h] = new myType[_sizeY];
	}
	MyLogger::log()->debug("[MyMatrix][allocate] Data allocated");
}

template <class myType>
void MyMatrix<myType>::allocate(unsigned int x, unsigned int y){
	_sizeX = x;_sizeY = y;
	allocate();
}

template <class myType>
void MyMatrix<myType>::deallocate(){
	MyLogger::log()->debug("[MyMatrix][deallocate] Dealocating data %ix%i",_sizeX,_sizeY);
	if(data){
		MyLogger::log()->debug("[MyMatrix][deallocate] Data exist, Freeing Memory");
		for(unsigned int h=0; h < _sizeX; ++h){
			if(data[h])
				delete [] data[h];
			data[h] = 0;
		}
		delete [] data;
	}
	MyLogger::log()->debug("[MyMatrix][deallocate] Data dealocated");
	_sizeX = 0; _sizeY = 0;
	data = 0;
}
/**
 *******************************
 * Metodos
 *******************************
 */

template <class myType>
void MyMatrix<myType>::reset(myType def){
	for(unsigned int x=0; x<_sizeX; ++x){
		for(unsigned int y=0; y<_sizeY; ++y){
			data[x][y]= def;
		}
	}
}

template <class myType>
unsigned int MyMatrix<myType>::sX(){
	return _sizeX;
}

template <class myType>
unsigned int MyMatrix<myType>::sY(){
	return _sizeY;
}

template <class myType>
myType MyMatrix<myType>::getValue(unsigned int x, unsigned int y){
	return data[x][y];
}

template <class myType>
myType & MyMatrix<myType>::at(unsigned int x, unsigned int y){
	return data[x][y];
}

template <class myType>
myType & MyMatrix<myType>::operator () (unsigned int x, unsigned int y){
	return data[x][y];
}

#endif
