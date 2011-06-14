/*
 * BinaryOutput.cpp
 *
 *  Created on: 13-06-2011
 *      Author: juanin
 */

#include "BinaryOutput.h"

BinaryOutput::BinaryOutput() {
	// TODO Auto-generated constructor stub
	cout << "::Constructing " << name() << endl;
}

BinaryOutput::~BinaryOutput() {
	// TODO Auto-generated destructor stub
	cout << "::Deleting " << name() << endl;
}

string BinaryOutput::name(){
	return "BinaryOutput";
}

void BinaryOutput::writeData(void* data){
	cout << "::Writing " << name() << endl;
}
