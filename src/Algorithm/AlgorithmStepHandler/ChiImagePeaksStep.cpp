/*
 * ChiImagePeaksStep.cpp
 *
 *  Created on: 12-06-2011
 *      Author: juanin
 */

#include "ChiImagePeaksStep.h"

ChiImagePeaksStep::ChiImagePeaksStep() {
	// TODO Auto-generated constructor stub

}

ChiImagePeaksStep::~ChiImagePeaksStep() {
	// TODO Auto-generated destructor stub
}

string ChiImagePeaksStep::name(){
	return "ChiImagePeaks Step";
}

void ChiImagePeaksStep::handleData(){
	cout << name() << " Data" << endl;
	next->handleData();
}
