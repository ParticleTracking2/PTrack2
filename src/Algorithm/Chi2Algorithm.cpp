/*
 * Chi2Algorithm.cpp
 *
 *  Created on: 12-06-2011
 *      Author: juanin
 */

#include "Chi2Algorithm.h"

Chi2Algorithm::Chi2Algorithm() {
	// TODO Auto-generated constructor stub
}

Chi2Algorithm::~Chi2Algorithm() {
	// TODO Auto-generated destructor stub
}

void Chi2Algorithm::setInitialValues(ParameterContainer *pc){
	pc_chi = pc;
}

void Chi2Algorithm::run(){
	cout << "Running Chi2Algorithm" << endl;
	ArgsProcessor *proc = ArgsProcessor::getInstance();
	AlgorithmStepHandler ash;

	ash.add(new NormalizeStep());
	ash.add(new ChiImageStep());
	ash.add(new PeaksStep());
	ash.add(new ParticleGridStep());
	ash.add(new ChiDifferenceStep());
	// Si esta el parametro hdensity
	if(proc->hasKey("-hdensity")){
		ash.add(new AddMissedPeaks_Step());
	}

	ash.handleData(pc_chi);
}
