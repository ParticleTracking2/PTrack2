/*
 * ChiImageStep.cpp
 *
 *  Created on: 26/08/2011
 *      Author: juanin
 */

#include "ChiImageStep.h"

ChiImageStep::ChiImageStep() {
	// TODO Auto-generated constructor stub

}

ChiImageStep::~ChiImageStep() {
	// TODO Auto-generated destructor stub
}

void ChiImageStep::handleData(ParameterContainer *pc){
	unsigned int os = (unsigned int)pc->getParam("iOS")->getDataInt();
	unsigned int ss = (unsigned int)pc->getParam("iSS")->getDataInt();
	double d = pc->getParam("dD")->getDataDouble();
	double w = pc->getParam("dW")->getDataDouble();

	MyImage *ipf = new MyImage(ss,ss);

	double absolute;
	double ipfval;
	for(unsigned int x=0; x < ss; ++x)
		for(unsigned int y=0; y < ss; ++y){
			absolute = abs(sqrt((x-os)*(x-os) + (y-os)*(y-os)));
			ipfval = (1.0 - tanh((absolute - d/2.0)/w))/2.0;
			ipf->setPixel(x,y,(unsigned char)(ipfval*255));
		}

	ipf->display();
	if(next)
		next->handleData(pc);
}
