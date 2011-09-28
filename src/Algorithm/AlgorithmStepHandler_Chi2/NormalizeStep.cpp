/*
 * Normalize.cpp
 *
 *  Created on: 12-06-2011
 *      Author: juanin
 */

#include "NormalizeStep.h"

/**
 *******************************
 * Metodos
 *******************************
 */
void NormalizeStep::handleData(ParameterContainer *pc){
	printDescription();
	MyImage *img = (MyImage *)pc->popParam("image")->getData();
//	img->writeToFile("img-cpp.txt");
	img->normalize();
//	img->writeToFile("nimg-cpp.txt");
	pc->addParam("normal_image", new Container(img), "[MyImage] Imagen normalizada (Invertidos los colores)");

	nextStep(pc);
}

void NormalizeStep::printDescription(){
	cout << "1.- Normalizar la imagen (invertir colores)" << endl;
}
