/*
 * PeaksStep.cpp
 *
 *  Created on: 12/09/2011
 *      Author: juanin
 */

#include "PeaksStep.h"

/**
 *******************************
 * Constructores
 *******************************
 */
PeaksStep::PeaksStep(){
	_threshold = 5;
	_minsep = 1;
	_mindistance = 5;
	chi_img = 0;
}

/**
 *******************************
 * Metodos
 *******************************
 */
void PeaksStep::handleData(ParameterContainer *pc){
	printDescription();
	chi_img = (Array2D<double> *)pc->getParam("chi_image")->getData();

	vector<MyPeak> *peaks = new vector<MyPeak>();

	for(unsigned int x=0; x < chi_img->getWidth(); ++x)
		for(unsigned int y=0; y < chi_img->getHeight(); ++y){
			if(chi_img->getValue(x,y) > _threshold){
				if(findLocalMinimum(chi_img,x,y)){
					MyPeak local(x,y, chi_img->getValue(x,y));
					peaks->push_back(local);
				}
			}
		}

	cout << "Peaks detected: " << peaks->size() << " Of " << chi_img->getHeight()*chi_img->getWidth() << endl;
	sort(peaks->begin(), peaks->end(), MyPeak::compare);
	validatePeaks(peaks);

	pc->addParam("peaks", new Container(peaks), "[vector<MyPeak>] Maximos encontrados a partir de la imagen Chi2");

	if(next)
		next->handleData(pc);
}

// Eliminar los que no cumplen con la minima distancia
void PeaksStep::validatePeaks(vector<MyPeak> *peaks){
	int difx = 0;
	int dify = 0;
	for(unsigned int i=0; i < peaks->size(); ++i){
		for(unsigned int j=i+1; j < peaks->size(); ++j){
			difx = peaks->at(i).getX() - peaks->at(j).getX();
			dify = peaks->at(i).getY() - peaks->at(j).getY();

			if(sqrt(difx*difx + dify*dify) < _mindistance){
				peaks->erase(peaks->begin()+(i-1));
			}
		}
	}
}

bool PeaksStep::findLocalMinimum(Array2D<double> *img, unsigned int imgX, unsigned int imgY){
	int currentX = 0;
	int currentY = 0;
	for(int localX = _minsep; localX >= -_minsep; --localX){
		currentX = (imgX+localX);
		if(currentX < 0)
			currentX = img->getWidth() + currentX;
		currentX = currentX % img->getWidth();

		for(int localY = _minsep; localY >= -_minsep; --localY){
			currentY = (imgY+localY);
			if(currentY < 0)
				currentY = img->getHeight() + currentY;
			currentY = currentY % img->getHeight();

			if(img->getValue(imgX, imgY) <= img->getValue(currentX, currentY))
				return false;
		}
	}
	return true;
}

void PeaksStep::setThreshold(int threshold){
	_threshold = threshold;
}

void PeaksStep::setMinSeparation(int minsep){
	_minsep = minsep;
}

void PeaksStep::setMinDistance(int mindistance){
	_mindistance = mindistance;
}
