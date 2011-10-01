//============================================================================
// Name        : CC69E
// Author      : Juan Silva
// Version     : 0.01b
// Copyright   : GLP
// Description : Primary structure of particle recognition software.
//============================================================================

#include "ArgsProcessor.h"
#include "Image/ImageFactory.h"
#include "Algorithm/Chi2Algorithm.h"
#include "Container/Container.h"
#include "Container/Array2D.h"
#include "Container/Array1D.h"
#include "Container/ParameterContainer.h"
#include "Output/Output.h"
#include "Output/BinaryOutput.h"
#include "Output/PlainOutput.h"
#include "Output/ConnectorOutput.h"

#include <math.h>
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {

	ArgsProcessor *proc = ArgsProcessor::getInstance();
	proc->setArgs(argc, argv);

	ImageFactory *_if = ImageFactory::getInstance();
	MyImage *img = _if->makeImgFromFile(proc->getArgAsString("-i"));

	ParameterContainer *pc = new ParameterContainer();
	// Agregar Imagen
	pc->addParam("image", new Container(img), "[MyImage] Imagen de entrada");
	pc->addParam("dD",new Container(proc->getArgAsDouble("-d")), "[double] Parametro D para generar la imagen de particula ideal");
	pc->addParam("dW",new Container(proc->getArgAsDouble("-w")), "[double] Parametro W para generar la imagen de particula ideal y la funcion Chi2");

	// Agregar tamaño de particula ideal
	int ss = 2*floor((proc->getArgAsDouble("-d")/2)+(4*proc->getArgAsDouble("-w")/2))-1;
	pc->addParam("iSS", new Container(ss), "[int] Tamaño de la particula ideal");

	// (size-1)/2 of ideal particle image
	int os = ((ss-1)/2);
	pc->addParam("iOS", new Container(os), "[int] (tamaño-1)/2 de la paricula ideal");

	Algorithm *alg = new Chi2Algorithm();
	alg->setInitialValues(pc);
	alg->run();

	Output *outp = new PlainOutput();
	outp->writeData(0);
	delete outp;

	return 0;
}
