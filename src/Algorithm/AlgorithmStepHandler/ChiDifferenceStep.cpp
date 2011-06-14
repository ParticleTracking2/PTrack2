/*
 * ChiDifferenceStep.cpp
 *
 *  Created on: 12-06-2011
 *      Author: juanin
 */

#include "ChiDifferenceStep.h"

ChiDifferenceStep::ChiDifferenceStep() {
	// TODO Auto-generated constructor stub

}

ChiDifferenceStep::~ChiDifferenceStep() {
	// TODO Auto-generated destructor stub
}

string ChiDifferenceStep::name(){
	return "ChiDifference Step";
}

void ChiDifferenceStep::handleData(){
	cout << name() << " Data" << endl;
	if(next)
		next->handleData();
}
