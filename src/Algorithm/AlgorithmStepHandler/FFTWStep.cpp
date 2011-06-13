/*
 * FFTWStep.cpp
 *
 *  Created on: 13-06-2011
 *      Author: juanin
 */

#include "FFTWStep.h"

FFTWStep::FFTWStep() {
	// TODO Auto-generated constructor stub

}

FFTWStep::~FFTWStep() {
	// TODO Auto-generated destructor stub
}

string FFTWStep::name(){
	return "FFTW Step";
}

void FFTWStep::handleData(){
	cout << name() << " Data" << endl;
	next->handleData();
}
