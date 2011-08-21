/*
 * CUFFTStep.cpp
 *
 *  Created on: 13-06-2011
 *      Author: juanin
 */

#include "CUFFTStep.h"

string CUFFTStep::name(){
	return "CUFFT Step";
}
/**
 *******************************
 * Constructores y Destructores
 *******************************
 */
CUFFTStep::CUFFTStep() {
	// TODO Auto-generated constructor stub
}

CUFFTStep::~CUFFTStep() {
	// TODO Auto-generated destructor stub
}

/**
 *******************************
 * Metodos
 *******************************
 */
void CUFFTStep::handleData(){
	cout << name() << " Data" << endl;
	if(next)
		next->handleData();
}
