/*
 * Container.cpp
 *
 *  Created on: 12-06-2011
 *      Author: juanin
 */

#include "Container.h"

/**
 *******************************
 * Constructores y Destructores
 *******************************
 */
Container::Container() {
	// Do nothing
}
Container::Container(int integer){
	myint = integer;
}

Container::Container(double dou){
	mydouble = dou;
}

Container::Container(string str){
	mystring = str;
}

Container::Container(void* data){
	mydata = data;
}

Container::Container(void** data){
	mydata2 = data;
}

Container::~Container() {
	// Do Nothing
}

/**
 *******************************
 * Metodos
 *******************************
 */
void Container::setData(int integer){
	myint = integer;
}

void Container::setData(double dou){
	mydouble = dou;
}

void Container::setData(string str){
	mystring = str;
}

void Container::setData(void* data){
	mydata = data;
}

void Container::setData(void** data){
	mydata2 = data;
}

void* Container::getData(){
	return mydata;
}

void** Container::getData2(){
	return mydata2;
}

int Container::getDataInt(){
	return myint;
}

double Container::getDataDouble(){
	return mydouble;
}

string Container::getDataString(){
	return mystring;
}
