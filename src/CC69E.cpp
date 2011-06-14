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
#include "Container/ParameterContainer.h"
#include "Output/Output.h"
#include "Output/BinaryOutput.h"
#include "Output/PlainOutput.h"
#include "Output/ConnectorOutput.h"

#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {

	ArgsProcessor *proc = ArgsProcessor::getInstance();
	proc->setArgs(argc, argv);

	ImageFactory *_if = ImageFactory::getInstance();
	_if->makeImgFromFile(IMAGE_JPG);
	_if->makeImgFromFile(IMAGE_PNG);
	_if->makeImgFromFile(IMAGE_TIFF);

	ParameterContainer *pc = new ParameterContainer();
	pc->addParam("myint", new Container(new int(1)));

	Algorithm *alg = new Chi2Algorithm();
	alg->setInitialValues(pc);
	alg->run();

	Output *outp = new PlainOutput();
	outp->writeData(0);
	delete outp;

	outp = new BinaryOutput();
	outp->writeData(0);
	delete outp;

	outp = new ConnectorOutput();
	outp->writeData(0);
	delete outp;

	return 0;
}
