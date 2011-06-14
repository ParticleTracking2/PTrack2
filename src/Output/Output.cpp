/*
 * Output.cpp
 *
 *  Created on: 13-06-2011
 *      Author: juanin
 */

#include "Output.h"

string Output::name(){
	return "Output";
}

void Output::writeData(void* data){
	cout << "::Writing " << name() << endl;
}
