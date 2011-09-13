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
	img->normalize();

	pc->addParam("normal_image", new Container(img), "[MyImage] Imagen normalizada (Invertidos los colores)");

	if(next)
		next->handleData(pc);
}
