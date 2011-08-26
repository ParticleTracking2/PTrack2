/*
 * PlainOutput.cpp
 *
 *  Created on: 13-06-2011
 *      Author: juanin
 */

#include "PlainOutput.h"

PlainOutput::PlainOutput() {
	// TODO Auto-generated constructor stub
	cout << "::Constructing PlainOutput" << endl;
}

PlainOutput::~PlainOutput() {
	// TODO Auto-generated destructor stub
	cout << "::Deleting PlainOutput" << endl;
}

void PlainOutput::writeData(void* data){
	cout << "::Writing PlainOutput" << endl;
}
