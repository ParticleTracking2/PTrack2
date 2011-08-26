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

	unsigned char hi = 125;
	unsigned char lo = 125;

	// Obtener valores Maximos y minimos de color.
	for(unsigned int x =0; x < img->getWidth(); ++x)
		for(unsigned int y =0; y < img->getHeight(); ++y){
			if(hi < img->getPixel(x,y))
				hi = img->getPixel(x,y);
			if(lo > img->getPixel(x,y))
				lo = img->getPixel(x,y);
		}
	//cout << "Hi: " << (int)hi << " Lo: " << (int)lo << endl;

	// Normalizar Imagen (Invertir colores)
	double newval;
	double dif = hi-lo;
	for(unsigned int x =0; x < img->getWidth(); ++x)
		for(unsigned int y =0; y < img->getHeight(); ++y){
			newval = (hi-img->getPixel(x,y)*1.0)/dif;
			img->setPixel(x,y,(unsigned char)(newval*255));
		}

	if(next)
		next->handleData(pc);
}
