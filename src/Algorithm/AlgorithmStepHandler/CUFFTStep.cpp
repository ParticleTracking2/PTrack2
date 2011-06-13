/*
 * CUFFTStep.cpp
 *
 *  Created on: 13-06-2011
 *      Author: juanin
 */

#include "CUFFTStep.h"

CUFFTStep::CUFFTStep() {
	// TODO Auto-generated constructor stub

}

CUFFTStep::~CUFFTStep() {
	// TODO Auto-generated destructor stub
}

string CUFFTStep::name(){
	return "CUFFT Step";
}

void CUFFTStep::handleData(){
	cout << name() << " Data" << endl;
	next->handleData();
}
