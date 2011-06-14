/*
 * PlainOutput.cpp
 *
 *  Created on: 13-06-2011
 *      Author: juanin
 */

#include "PlainOutput.h"

PlainOutput::PlainOutput() {
	// TODO Auto-generated constructor stub
	cout << "::Constructing " << name() << endl;
}

PlainOutput::~PlainOutput() {
	// TODO Auto-generated destructor stub
	cout << "::Deleting " << name() << endl;
}

string PlainOutput::name(){
	return "PlainOutput";
}

void PlainOutput::writeData(void* data){
	cout << "::Writing " << name() << endl;
}
