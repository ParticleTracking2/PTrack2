/*
 * particleGridStep.cpp
 *
 *  Created on: 12-06-2011
 *      Author: juanin
 */

#include "ParticleGridStep.h"

string ParticleGridStep::name(){
	return "ParticleGridStep";
}
/**
 *******************************
 * Constructores y Destructores
 *******************************
 */
ParticleGridStep::ParticleGridStep() {
	// TODO Auto-generated constructor stub
}

ParticleGridStep::~ParticleGridStep() {
	// TODO Auto-generated destructor stub
}

/**
 *******************************
 * Metodos
 *******************************
 */
void ParticleGridStep::handleData(){
	cout << name() << " Data" << endl;
	if(next)
		next->handleData();
}
