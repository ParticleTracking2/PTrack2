/*
 * Matrix.h
 *
 *  Created on: 31/08/2011
 *      Author: juanin
 */
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
MyMatrix<myType>::MyMatrix(unsigned int sX, unsigned int sy){
	data = 0;
	_sizeX = sX; _sizeY = sy;
	allocate();
}

template <class myType>
MyMatrix<myType>::MyMatrix(unsigned int sX, unsigned int sy, myType def){
	data = 0;
	_sizeX = sX; _sizeY = sy;
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

	data = (myType**)malloc(_sizeX*sizeof(myType));
	for(unsigned int h=0; h < _sizeY; ++h){
		data[h] = (myType*)malloc(_sizeY*sizeof(myType));
	}
}

template <class myType>
void MyMatrix<myType>::allocate(unsigned int sX, unsigned int sy){
	_sizeX = sX;_sizeY = sy;
	allocate();
}

template <class myType>
void MyMatrix<myType>::deallocate(){
	if(data){
		for(unsigned int h=0; h < _sizeY; ++h){
			if(data[h])
				free(data[h]);
		}
		free(data);
	}
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
