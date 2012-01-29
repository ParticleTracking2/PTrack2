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
	clear();
}
Container::Container(int integer){
	clear();
	myint = integer;
}

Container::Container(double dou){
	clear();
	mydouble = dou;
}

Container::Container(string str){
	clear();
	mystring = str;
}

Container::Container(char* str){
	clear();
	mystring = str;
}

Container::~Container() {
	clear();
}

void Container::clear() {
	myint = -1;
	mydouble = -1;
	mystring = "";
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

void Container::setData(char *str){
	mystring = str;
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

void Container::setDescription(string desc){
	_description = desc;
}

string Container::getDescription(){
	return _description;
}

