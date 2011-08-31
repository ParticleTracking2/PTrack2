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

	double hi = img->getValue(0,0);
	double lo = img->getValue(0,0);

	// Obtener valores Maximos y minimos de color.
	for(unsigned int x =0; x < img->getWidth(); ++x)
		for(unsigned int y =0; y < img->getHeight(); ++y){
			if(hi < img->getValue(x,y))
				hi = img->getValue(x,y);
			if(lo > img->getValue(x,y))
				lo = img->getValue(x,y);
		}
	//cout << "Hi: " << hi << " Lo: " << lo << endl;

	// Normalizar Imagen (Invertir colores)
	Array2D<double>* normal_img = new Array2D<double>(img->getWidth(), img->getHeight());
	double newval;
	double dif = hi-lo;
	for(unsigned int x =0; x < img->getWidth(); ++x)
		for(unsigned int y =0; y < img->getHeight(); ++y){
			newval = (hi-img->getValue(x,y)*1.0)/dif;
			normal_img->setValue(x,y,newval);
		}

	pc->addParam("normal_image", new Container(normal_img));

	if(next)
		next->handleData(pc);
}
