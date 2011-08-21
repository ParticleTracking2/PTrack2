/*
 * ChiImagePeaksStep.cpp
 *
 *  Created on: 12-06-2011
 *      Author: juanin
 */

#include "ChiImagePeaksStep.h"

string ChiImagePeaksStep::name(){
	return "ChiImagePeaks Step";
}
/**
 *******************************
 * Constructores y Destructores
 *******************************
 */
ChiImagePeaksStep::ChiImagePeaksStep() {
	// TODO Auto-generated constructor stub

}

ChiImagePeaksStep::~ChiImagePeaksStep() {
	// TODO Auto-generated destructor stub
}

/**
 *******************************
 * Metodos
 *******************************
 */
void ChiImagePeaksStep::handleData(){
	cout << name() << " Data" << endl;
	if(next)
		next->handleData();
}
