/*
 * ConnectorOutput.cpp
 *
 *  Created on: 13-06-2011
 *      Author: juanin
 */

#include "ConnectorOutput.h"

ConnectorOutput::ConnectorOutput() {
	// TODO Auto-generated constructor stub
	cout << "::Constructing " << name() << endl;
}

ConnectorOutput::~ConnectorOutput() {
	// TODO Auto-generated destructor stub
	cout << "::Deleting " << name() << endl;
}

string ConnectorOutput::name(){
	return "ConnectorOutput";
}
void ConnectorOutput::writeData(void* data){
	cout << "::Writing " << name() << endl;
}
