/*
 * Array1D.h
 *
 *  Created on: 31/08/2011
 *      Author: juanin
 */
#include <vector>

#ifndef ARRAY1D
#define ARRAY1D

using namespace std;

template <class myType>
class Array1D{
private:
	unsigned int _size;
	vector <myType> data;

	void allocateData();
public:
	Array1D();
	Array1D(unsigned int width);
	~Array1D();
	void setSize(unsigned int width);
	unsigned int getSize();

	void setValue(unsigned int x, myType val);
	myType getValue(unsigned int x);

	void reset(myType def = 0);
};

/**
 *******************************
 * Constructores y Destructores
 *******************************
 */
template <class myType>
Array1D<myType>::Array1D() {
}

template <class myType>
Array1D<myType>::Array1D(unsigned int width){
	setSize(width);
	reset();
}

template <class myType>
Array1D<myType>::~Array1D() {
	// Some
}

template <class myType>
void Array1D<myType>::allocateData(){
	data.assign(_size, 0);
}

/**
 *******************************
 * Metodos
 *******************************
 */
template <class myType>
void Array1D<myType>::setSize(unsigned int width){
	this->_size = width;
}

template <class myType>
unsigned int Array1D<myType>::getSize(){
	return this->_size;
}

template <class myType>
void Array1D<myType>::setValue(unsigned int x, myType val){
	if(x < _size)
		data[x] = val;
}

template <class myType>
myType Array1D<myType>::getValue(unsigned int x){
	if(x < _size)
		return data[x];
	return 0;
}

template <class myType>
void Array1D<myType>::reset(myType def){
	if(data.empty())
		allocateData();

	for(unsigned int x=0; x<_size; ++x)
		data[x]= def;
}

#endif
