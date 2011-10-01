/*
 * ParticleGridStep.cpp
 *
 *  Created on: 12/09/2011
 *      Author: juanin
 */

#include "ParticleGridStep.h"

void ParticleGridStep::handleData(ParameterContainer *pc){
	vector<MyPeak> *peaks = (vector<MyPeak> *)pc->getData("peaks");
	Array2D<double> *img = (Array2D<double>*)pc->getData("normal_image");
	unsigned int os = (unsigned int)pc->getParam("iOS")->getDataInt();

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
	vector<double> *px = new vector<double>();
	vector<double> *py = new vector<double>();
	for(unsigned int i=0; i < peaks->size(); ++i){
		px->push_back(1.0*peaks->at(i).getX());
		py->push_back(1.0*peaks->at(i).getY());
	}

	generateGrid(peaks, px, py, os, img, grid_x, grid_y, over);

//	MyUtils::writeToFile(grid_x, "grid_x-cpp.txt");
//	MyUtils::writeToFile(grid_y, "grid_y-cpp.txt");
//	MyUtils::writeToFile(over, "over-cpp.txt");

	pc->addParam("grid_x", new Container(grid_x), "[Array2D<double>]");
	pc->addParam("grid_y", new Container(grid_y), "[Array2D<double>]");
	pc->addParam("over", new Container(over), "[Array2D<int>]");
	pc->addParam("px", new Container(px), "[vector<double>]");
	pc->addParam("py", new Container(py), "[vector<double>]");

	nextStep(pc);
}

unsigned int ParticleGridStep::generateGrid(vector<MyPeak> *peaks, vector<double> *px, vector<double> *py, unsigned int shift, Array2D<double> *img, Array2D<double> *grid_x, Array2D<double> *grid_y, Array2D<int> *over){
	unsigned int half=(shift+2);
	unsigned int counter = 0;
	unsigned int currentX, currentY;
	double currentDistance = 0.0;
	double currentDistanceAux = 0.0;

	if(!peaks->empty())
	for(int npks = peaks->size()-1; npks >= 0; npks--){
		for(unsigned int localX=0; localX < 2*half+1; ++localX)
			for(unsigned int localY=0; localY < 2*half+1; ++localY){
				currentX = (int)round(px->at(npks)) - shift + (localX - half);
				currentY = (int)round(py->at(npks)) - shift + (localY - half);

				if( 0 <= currentX && currentX < img->getWidth() && 0 <= currentY && currentY < img->getHeight() ){
					currentDistance =
							sqrt(grid_x->getValue(currentX, currentY)*grid_x->getValue(currentX, currentY)
								+ grid_y->getValue(currentX, currentY)*grid_y->getValue(currentX, currentY));

					currentDistanceAux =
							sqrt(1.0*(1.0*localX-half+peaks->at(npks).getX() - px->at(npks))*(1.0*localX-half+peaks->at(npks).getX() - px->at(npks)) +
								 1.0*(1.0*localY-half+peaks->at(npks).getY() - py->at(npks))*(1.0*localY-half+peaks->at(npks).getY() - py->at(npks)));

					double tmpx = (1.0*localX-half+peaks->at(npks).getX())-px->at(npks);
					double tmpy = (1.0*localY-half+peaks->at(npks).getY())-py->at(npks);
					if(currentDistance >= currentDistanceAux){
						over->setValue(currentX, currentY, npks+1);
						grid_x->setValue(currentX, currentY, tmpx);
						grid_y->setValue(currentX, currentY, tmpy);
						counter++;
					}
				}

			}
	}

	cout << "Total pgrid: " << 1.0*counter/peaks->size() << "; counter: " << counter << endl;
	return counter;
}

void ParticleGridStep::printDescription(){
	cout << "4.- Generar matrices auxiliuares" << endl;
}
