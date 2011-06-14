/*
 * Chi2Algorithm.cpp
 *
 *  Created on: 12-06-2011
 *      Author: juanin
 */

#include "Chi2Algorithm.h"

string Chi2Algorithm::name(){
	return "CHi^2 Algorithm";
}

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
	cout << "Running " << name() << endl;

	AlgorithmStepHandler ash;

	ash.add(new Chi2Step());
	ash.add(new ChiDifferenceStep());
	ash.add(new ChiImagePeaksStep());
	ash.add(new CUFFTStep());
	ash.add(new FFTWStep());
	ash.add(new NewtonParticleCenterStep());
	ash.add(new NewtonParticleDWStep());
	ash.add(new NormalizeStep());
	ash.add(new ParticleGridStep());

	ash.handleData();
}
