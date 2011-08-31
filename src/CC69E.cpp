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

	cout << "Values: " << proc->getArgAsDouble("-d") << endl;
	cout << "Values: " << proc->getArgAsDouble("-w") << endl;
	cout << "Values: " << proc->getArgAsString("-i") << endl;

	ImageFactory *_if = ImageFactory::getInstance();
	MyImage *img = _if->makeImgFromFile(proc->getArgAsString("-i"));

	ParameterContainer *pc = new ParameterContainer();
	// Agregar Imagen
	pc->addParam("image", new Container(img));
	pc->addParam("dD",new Container(proc->getArgAsDouble("-d")));
	pc->addParam("dW",new Container(proc->getArgAsDouble("-w")));

	// Agregar tamaño de particula ideal
	int ss = 2*floor((proc->getArgAsDouble("-d")/2)+(4*proc->getArgAsDouble("-w")/2))-1;
	pc->addParam("iSS", new Container(ss));

	// (size-1)/2 of ideal particle image
	int os = ((ss-1)/2);
	pc->addParam("iOS", new Container(os));

	Algorithm *alg = new Chi2Algorithm();
	alg->setInitialValues(pc);
	alg->run();

	Output *outp = new PlainOutput();
	outp->writeData(0);
	delete outp;

	return 0;
}
