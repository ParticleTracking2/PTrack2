/*
 * ArgsProcessor.cpp
 *
 *  Created on: 13-06-2011
 *      Author: juanin
 */

#include "ArgsProcessor.h"

ArgsProcessor* ArgsProcessor::myInstance = 0;

ArgsProcessor::ArgsProcessor() {
	cout << "Constructing " <<  name() << endl;
}

ArgsProcessor::~ArgsProcessor() {
	cout << "Destructing " <<  name() << endl;
}

string ArgsProcessor::name() {
	return "ArgsProcessor";
}

ArgsProcessor *ArgsProcessor::getInstance(){
	if(!myInstance)
			myInstance = new ArgsProcessor();
		return myInstance;
}

void ArgsProcessor::setArgs(int argcount, char* argvalues[]){
	cout << "Args Count = " << argcount << endl;
	for(int i = 0; i < argcount; i++)
		cout << "Args Values[" << i << "] = " << argvalues[i] << endl;
}
