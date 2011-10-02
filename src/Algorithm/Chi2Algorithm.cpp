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

	ash.add(new NormalizeStep()); 		// OK
	ash.add(new ChiImageStep()); 		// OK
	ash.add(new PeaksStep()); 			// OK
	ash.add(new ParticleGridStep()); 	// OK con problemas de compilador? al asignar los valores a grid_x e grid_y con indice x=9 y y=0
	ash.add(new ChiDifferenceStep()); 	// OK
	// Si esta el parametro hdensity
	if(proc->hasKey("-hdensity")){
		ash.add(new AddMissedPeaks_Step());	// [+/-] Recoge todos los puntos, sin embargo al generar las grillas de particulas estas no tienen el mismo valor.
		ash.add(new ReComputeGridAndDiff());
	}
	ash.add(new Chi2Minimization());
	if(proc->hasKey("-hdensity")){
		ash.add(new CheckParticlesStep());
	}

	ash.handleData(pc_chi);
}
