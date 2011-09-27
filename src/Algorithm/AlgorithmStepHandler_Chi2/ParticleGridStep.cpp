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

	int maxDimension;
	if(img->getWidth() > img->getHeight())
		maxDimension = img->getWidth();
	else
		maxDimension = img->getHeight();

	Array2D<double> *grid_x = new Array2D<double>(img->getWidth(), img->getHeight(), 1.0*maxDimension);
	Array2D<double> *grid_y = new Array2D<double>(img->getWidth(), img->getHeight(), 1.0*maxDimension);
	Array2D<int> *over = new Array2D<int>(img->getWidth(), img->getHeight(), 0);
	// Nota px y py son puntos convertidos en double de cada uno de los peaks detectados.
	// Se reemplazaron por cada coordenada de los peaks

	unsigned int counter = generateGrid(peaks, ss, img, grid_x, grid_y, over);

	if(!peaks->empty()){
		cout << "Total pgrid: " << 1.0*counter/peaks->size() << "; counter: " << counter << endl;
	}

	pc->addParam("grid_x", new Container(grid_x), "[Array2D<double>]");
	pc->addParam("grid_y", new Container(grid_y), "[Array2D<double>]");
	pc->addParam("over", new Container(over), "[Array2D<int>]");

	if(next)
		next->handleData(pc);
}

unsigned int ParticleGridStep::generateGrid(vector<MyPeak> *peaks, unsigned int ss, Array2D<double> *img, Array2D<double> *grid_x, Array2D<double> *grid_y, Array2D<int> *over){
	unsigned int half=(int)(ceil((2.0*ss+3)/2.0));
	unsigned int counter = 0;
	unsigned int currentX, currentY;
	double currentDistance = 0.0;
	double currentDistanceAux = 0.0;

	if(!peaks->empty())
	for(int npks = peaks->size()-1; npks >= 0; --npks){
		for(unsigned int localX=0; localX < 2*half+1; ++localX)
			for(unsigned int localY=0; localY < 2*half+1; ++localY){
				currentX = (int)round(peaks->at(npks).getX()) - ss + (localX - half);
				currentY = (int)round(peaks->at(npks).getY()) - ss + (localY - half);
				if( 0 <= currentX && currentX < img->getWidth() && 0 <= currentY && currentY < img->getHeight() ){
					currentDistance =
							sqrt(grid_x->getValue(currentX, currentY)*grid_x->getValue(currentX, currentY)
								+ grid_y->getValue(currentX, currentY)*grid_y->getValue(currentX, currentY));
					currentDistanceAux =
							sqrt(1.0*(1.0*localX-half+peaks->at(npks).getX() - peaks->at(npks).getX())*(1.0*localX-half+peaks->at(npks).getX() - peaks->at(npks).getX()) +
								 1.0*(1.0*localY-half+peaks->at(npks).getY() - peaks->at(npks).getY())*(1.0*localY-half+peaks->at(npks).getY() - peaks->at(npks).getY()));

					if(currentDistance >= currentDistanceAux){
						over->setValue(currentX, currentY, npks+1);
						grid_x->setValue(currentX, currentY, (1.0*localX-half+peaks->at(npks).getX())-peaks->at(npks).getX());
						grid_y->setValue(currentX, currentY, (1.0*localY-half+peaks->at(npks).getY())-peaks->at(npks).getY());
						counter++;
					}
				}

			}
	}

	return counter;
}
