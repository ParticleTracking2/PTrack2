/*
 * ParticleGridStep.cpp
 *
 *  Created on: 12/09/2011
 *      Author: juanin
 */

#include "ParticleGridStep.h"

void ParticleGridStep::handleData(ParameterContainer *pc){
	printDescription();
	vector<MyPeak> *peaks = (vector<MyPeak> *)pc->getData("peaks");
	Array2D<double> *img = (Array2D<double>*)pc->getData("normal_image");
	unsigned int ss = (unsigned int)pc->getParam("iSS")->getDataInt();

	unsigned int half=(int)(ceil((2.0*ss+3)/2.0));
	int maxDimension;
	if(img->getWidth() > img->getHeight())
		maxDimension = img->getWidth();
	else
		maxDimension = img->getHeight();

	Array2D<double> *grid_x = new Array2D<double>(img->getWidth(), img->getHeight(), 1.0*maxDimension);
	Array2D<double> *grid_y = new Array2D<double>(img->getWidth(), img->getHeight(), 1.0*maxDimension);
	Array2D<int> *over = new Array2D<int>(img->getWidth(), img->getHeight(), 0);
	vector<double> px, py;

	if(!peaks->empty())
	for(unsigned int i=0; i<peaks->size(); ++i){
		px.push_back(1.0*peaks->at(i).getX());
		py.push_back(1.0*peaks->at(i).getY());
	}

	unsigned int counter = 0;
	unsigned int currentX, currentY;
	double currentDistance = 0.0;
	double currentDistanceAux = 0.0;
	if(!peaks->empty())
	for(unsigned int npks = peaks->size()-1; npks >= 0; --npks){
		for(unsigned int localX=0; localX < 2*half+1; ++localX)
			for(unsigned int localY=0; localY < 2*half+1; ++localY){
				currentX = (int)round(px[npks]) - ss + (localX - half);
				currentY = (int)round(py[npks]) - ss + (localY - half);
				if( 0 <= currentX && currentX < img->getWidth() && 0 <= currentY && currentY < img->getHeight() ){
					currentDistance = sqrt(pow(grid_x->getValue(currentX, currentY),2) + pow(grid_y->getValue(currentX, currentY),2) );
					currentDistanceAux =
							sqrt(1.0*pow((1.0*localX-half+peaks->at(npks).getX() - px[npks]),2) +
								 1.0*pow((1.0*localY-half+peaks->at(npks).getY() - py[npks]),2));

					if(currentDistance >= currentDistanceAux){
						over->setValue(currentX, currentY, npks+1);
						grid_x->setValue(currentX, currentY, (1.0*localX-half+peaks->at(npks).getX())-px[npks]);
						grid_y->setValue(currentX, currentY, (1.0*localY-half+peaks->at(npks).getY())-py[npks]);
						counter++;
					}
				}

			}
	}

	if(!peaks->empty()){
		cout << "Total pgrid: " << 1.0*counter/peaks->size() << "; counter: " << counter << endl;
	}
	//pc->printInformation();

	if(next)
		next->handleData(pc);
}

