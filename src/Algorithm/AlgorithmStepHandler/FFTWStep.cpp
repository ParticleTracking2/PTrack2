/*
 * FFTWStep.cpp
 *
 *  Created on: 13-06-2011
 *      Author: juanin
 */

#include "FFTWStep.h"

string FFTWStep::name(){
	return "FFTW Step";
}
/**
 *******************************
 * Constructores y Destructores
 *******************************
 */
FFTWStep::FFTWStep() {
	// TODO Auto-generated constructor stub
}

FFTWStep::~FFTWStep() {
	// TODO Auto-generated destructor stub
}

/**
 *******************************
 * Metodos
 *******************************
 */
void FFTWStep::handleData(){
	cout << name() << " Data" << endl;
	if(next)
		next->handleData();
}
