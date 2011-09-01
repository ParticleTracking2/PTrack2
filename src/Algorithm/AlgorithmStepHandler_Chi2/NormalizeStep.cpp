/*
 * Normalize.cpp
 *
 *  Created on: 12-06-2011
 *      Author: juanin
 */

#include "NormalizeStep.h"

/**
 *******************************
 * Constructores y Destructores
 *******************************
 */
NormalizeStep::NormalizeStep() {
	// Do Nothing
}

NormalizeStep::~NormalizeStep() {
	// Do Nothing
}

/**
 *******************************
 * Metodos
 *******************************
 */
void NormalizeStep::handleData(ParameterContainer *pc){
	cout << "NormalizeStep Data" << endl;
	Container *container = pc->getParam("image");
	MyImage *img = (MyImage *)container->getData();
	img->normalize();

	pc->addParam("normal_image", new Container(img));

	if(next)
		next->handleData(pc);
}
